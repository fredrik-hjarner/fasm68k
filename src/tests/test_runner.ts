#!/usr/bin/env bun
// fasm68k test runner - validates test cases against expected outputs

import * as fs from 'fs';
import * as path from 'path';

// ============================================================================
// Types
// ============================================================================

interface ExpectedOutput {
  type: 'success_binary' | 'success_binary_match' | 'success_with_warnings' | 'error_expected' | 'output_contains';
  exitCode: number;
  description: string;
  asm: string;  // Inline assembly code (multiline string)
  // Binary validation
  binaryHex?: string;
  referenceFile?: string;
  // Error validation
  errorPattern?: string;
  errorRegex?: boolean;
  errorContains?: string;
  // Output validation
  stdoutContains?: string[];
  stderrContains?: string[];
  warnings?: string[];
}

interface TestCase {
  name: string;
  dir: string;
  asmFile: string;
  expectedFile: string;
  metadata: ExpectedOutput;
}

interface TestResult {
  name: string;
  passed: boolean;
  description: string;
  expected?: any;
  actual?: any;
  error?: string;
}

// ============================================================================
// Discovery
// ============================================================================

async function loadTestCase(testFile: string): Promise<any> {
  if (!fs.existsSync(testFile)) {
    return null;
  }
  
  try {
    // Use dynamic import to load the TypeScript file
    // Convert to file:// URL for proper module resolution
    const fileUrl = `file://${path.resolve(testFile)}`;
    const module = await import(fileUrl);
    return module.default;
  } catch (e) {
    throw new Error(`Failed to load test case from ${testFile}: ${e instanceof Error ? e.message : String(e)}`);
  }
}

async function discoverTestCases(casesDir: string): Promise<TestCase[]> {
  const cases: TestCase[] = [];
  
  if (!fs.existsSync(casesDir)) {
    console.error(`Test cases directory not found: ${casesDir}`);
    return cases;
  }
  
  async function searchDirectory(dir: string, basePath: string = ''): Promise<void> {
    const entries = fs.readdirSync(dir, { withFileTypes: true });
    
    for (const entry of entries) {
      if (entry.isFile() && entry.name.endsWith('.ts')) {
        // Found a .ts file directly
        const testFile = path.join(dir, entry.name);
        const testName = entry.name.replace(/\.ts$/, '');
        const testPath = basePath ? `${basePath}/${testName}` : testName;
        
        const metadata = await loadTestCase(testFile);
        
        if (metadata) {
          // Validate required fields
          if (!metadata.type || typeof metadata.exitCode !== 'number' || !metadata.description) {
            console.warn(`Warning: Test case ${testPath} missing required fields (type, exitCode, description), skipping`);
            continue;
          }
          
          if (!metadata.asm) {
            console.warn(`Warning: Test case ${testPath} missing 'asm' field, skipping`);
            continue;
          }
          
          cases.push({
            name: testPath.replace(/[\/\\]/g, '_'),
            dir: path.dirname(testFile),
            asmFile: metadata.asm,
            expectedFile: testFile,
            metadata
          });
        }
      } else if (entry.isDirectory()) {
        // Recursively search subdirectories
        const subDir = path.join(dir, entry.name);
        const subPath = basePath ? `${basePath}/${entry.name}` : entry.name;
        await searchDirectory(subDir, subPath);
      }
    }
  }
  
  await searchDirectory(casesDir);
  return cases;
}

// ============================================================================
// Utilities
// ============================================================================

function bytesToHex(bytes: Uint8Array | Buffer): string {
  return Array.from(bytes)
    .map(b => b.toString(16).padStart(2, '0'))
    .join('');
}

function findFasm68k(): string {
  // Try multiple possible locations
  const possiblePaths = [
    process.env.FASM68K_PATH,
    './fasm68k',
    '../fasm68k',
    '../../fasm68k/fasm68k',
    path.join(__dirname, '../../fasm68k/fasm68k'),
    path.join(__dirname, '../../../fasm68k/fasm68k'),
  ].filter(Boolean) as string[];

  for (const p of possiblePaths) {
    if (fs.existsSync(p) && fs.statSync(p).isFile()) {
      return p;
    }
  }

  // Default fallback
  return './fasm68k';
}

// ============================================================================
// Test Execution
// ============================================================================

interface ProcessResult {
  exitCode: number;
  stdout: string;
  stderr: string;
  binary: Buffer | null;
}

async function runFasm68k(asmCode: string, binFile: string, testDir: string): Promise<ProcessResult> {
  try {
    const fasm68kPath = findFasm68k();
    
    // Write inline assembly to a temporary file
    const tempAsmFile = path.join(testDir, 'temp_test.asm');
    fs.writeFileSync(tempAsmFile, asmCode);
    
    const proc = Bun.spawn([fasm68kPath, tempAsmFile, binFile], {
      stdio: ['pipe', 'pipe', 'pipe']
    });
    
    const stdout = await new Response(proc.stdout).text();
    const stderr = await new Response(proc.stderr).text();
    const exitCode = await proc.exited;
    
    // Clean up temp file
    if (fs.existsSync(tempAsmFile)) {
      fs.unlinkSync(tempAsmFile);
    }
    
    // Try to read binary output
    let binary = null;
    if (fs.existsSync(binFile)) {
      binary = fs.readFileSync(binFile);
    }
    
    return { exitCode, stdout, stderr, binary };
  } catch (e) {
    return {
      exitCode: 127,
      stdout: '',
      stderr: `Failed to run fasm68k: ${e}`,
      binary: null
    };
  }
}

// ============================================================================
// Validators
// ============================================================================

function validateSuccessBinary(testCase: TestCase, actual: ProcessResult): TestResult {
  const result: TestResult = {
    name: testCase.name,
    description: testCase.metadata.description,
    passed: false
  };
  
  if (actual.exitCode !== 0) {
    result.error = `Expected exit code 0 but got ${actual.exitCode}`;
    result.expected = { exitCode: 0 };
    result.actual = { exitCode: actual.exitCode, stderr: actual.stderr };
    return result;
  }
  
  if (!actual.binary) {
    result.error = `No binary output produced`;
    return result;
  }
  
  const expectedHex = testCase.metadata.binaryHex || '';
  const actualHex = bytesToHex(actual.binary);
  
  if (actualHex === expectedHex) {
    result.passed = true;
    return result;
  }
  
  result.error = `Binary mismatch`;
  result.expected = { binary: expectedHex };
  result.actual = { binary: actualHex };
  return result;
}

function validateSuccessBinaryMatch(testCase: TestCase, actual: ProcessResult): TestResult {
  const result: TestResult = {
    name: testCase.name,
    description: testCase.metadata.description,
    passed: false
  };
  
  if (actual.exitCode !== 0) {
    result.error = `Expected exit code 0 but got ${actual.exitCode}`;
    result.actual = { exitCode: actual.exitCode, stderr: actual.stderr };
    return result;
  }
  
  if (!actual.binary) {
    result.error = `No binary output produced`;
    return result;
  }
  
  const refFile = path.join(path.dirname(testCase.expectedFile), testCase.metadata.referenceFile || 'reference.bin');
  if (!fs.existsSync(refFile)) {
    result.error = `Reference file not found: ${refFile}`;
    return result;
  }
  
  const refBinary = fs.readFileSync(refFile);
  const actualHex = bytesToHex(actual.binary);
  const refHex = bytesToHex(refBinary);
  
  if (actualHex === refHex) {
    result.passed = true;
    return result;
  }
  
  result.error = `Binary does not match reference`;
  result.expected = { binary: refHex };
  result.actual = { binary: actualHex };
  return result;
}

function validateSuccessWithWarnings(testCase: TestCase, actual: ProcessResult): TestResult {
  const result: TestResult = {
    name: testCase.name,
    description: testCase.metadata.description,
    passed: false
  };
  
  if (actual.exitCode !== 0) {
    result.error = `Expected exit code 0 but got ${actual.exitCode}`;
    result.actual = { exitCode: actual.exitCode, stderr: actual.stderr };
    return result;
  }
  
  if (!actual.binary) {
    result.error = `No binary output produced`;
    return result;
  }
  
  // Check binary if specified
  if (testCase.metadata.binaryHex) {
    const actualHex = bytesToHex(actual.binary);
    if (actualHex !== testCase.metadata.binaryHex) {
      result.error = `Binary mismatch`;
      result.expected = { binary: testCase.metadata.binaryHex };
      result.actual = { binary: actualHex };
      return result;
    }
  }
  
  // Check warnings
  if (testCase.metadata.warnings && testCase.metadata.warnings.length > 0) {
    const fullOutput = actual.stderr + actual.stdout;
    for (const warning of testCase.metadata.warnings) {
      if (!fullOutput.includes(warning)) {
        result.error = `Expected warning not found: "${warning}"`;
        result.expected = { warnings: testCase.metadata.warnings };
        result.actual = { output: fullOutput.slice(0, 200) };
        return result;
      }
    }
  }
  
  result.passed = true;
  return result;
}

function validateErrorExpected(testCase: TestCase, actual: ProcessResult): TestResult {
  const result: TestResult = {
    name: testCase.name,
    description: testCase.metadata.description,
    passed: false
  };
  
  if (actual.exitCode === 0) {
    result.error = `Expected non-zero exit code but got 0 (assembly succeeded)`;
    result.expected = { exitCode: 'non-zero' };
    result.actual = { exitCode: 0 };
    return result;
  }
  
  // Check error pattern
  if (testCase.metadata.errorRegex && testCase.metadata.errorPattern) {
    const regex = new RegExp(testCase.metadata.errorPattern, 'i');
    const fullOutput = actual.stderr + actual.stdout;
    if (regex.test(fullOutput)) {
      result.passed = true;
      return result;
    }
    result.error = `Error message did not match pattern: ${testCase.metadata.errorPattern}`;
    result.expected = { errorPattern: testCase.metadata.errorPattern };
    result.actual = { output: fullOutput.slice(0, 200) };
    return result;
  }
  
  // Check error contains
  if (testCase.metadata.errorContains) {
    const fullOutput = actual.stderr + actual.stdout;
    if (fullOutput.includes(testCase.metadata.errorContains)) {
      result.passed = true;
      return result;
    }
    result.error = `Error message does not contain: "${testCase.metadata.errorContains}"`;
    result.expected = { errorContains: testCase.metadata.errorContains };
    result.actual = { output: fullOutput.slice(0, 200) };
    return result;
  }
  
  // If we just wanted a non-zero exit code, we're good
  result.passed = true;
  return result;
}

function validateOutputContains(testCase: TestCase, actual: ProcessResult): TestResult {
  const result: TestResult = {
    name: testCase.name,
    description: testCase.metadata.description,
    passed: true
  };
  
  if (actual.exitCode !== testCase.metadata.exitCode) {
    result.passed = false;
    result.error = `Expected exit code ${testCase.metadata.exitCode} but got ${actual.exitCode}`;
    return result;
  }
  
  // Check stdout
  if (testCase.metadata.stdoutContains) {
    for (const str of testCase.metadata.stdoutContains) {
      if (!actual.stdout.includes(str)) {
        result.passed = false;
        result.error = `stdout does not contain: "${str}"`;
        result.actual = { stdout: actual.stdout.slice(0, 200) };
        return result;
      }
    }
  }
  
  // Check stderr
  if (testCase.metadata.stderrContains) {
    for (const str of testCase.metadata.stderrContains) {
      if (!actual.stderr.includes(str)) {
        result.passed = false;
        result.error = `stderr does not contain: "${str}"`;
        result.actual = { stderr: actual.stderr.slice(0, 200) };
        return result;
      }
    }
  }
  
  return result;
}

// ============================================================================
// Main Test Runner
// ============================================================================

async function runAllTests(casesDir: string): Promise<TestResult[]> {
  const cases = await discoverTestCases(casesDir);
  const results: TestResult[] = [];
  
  console.log(`Found ${cases.length} test cases\n`);
  
  for (const testCase of cases) {
    const binFile = path.join(testCase.dir, 'output.bin');
    
    try {
      const actual = await runFasm68k(testCase.asmFile, binFile, testCase.dir);
      let result: TestResult;
      
      switch (testCase.metadata.type) {
        case 'success_binary':
          result = validateSuccessBinary(testCase, actual);
          break;
        case 'success_binary_match':
          result = validateSuccessBinaryMatch(testCase, actual);
          break;
        case 'success_with_warnings':
          result = validateSuccessWithWarnings(testCase, actual);
          break;
        case 'error_expected':
          result = validateErrorExpected(testCase, actual);
          break;
        case 'output_contains':
          result = validateOutputContains(testCase, actual);
          break;
        default:
          result = {
            name: testCase.name,
            description: testCase.metadata.description,
            passed: false,
            error: `Unknown test type: ${testCase.metadata.type}`
          };
      }
      
      results.push(result);
      
      // Clean up
      if (fs.existsSync(binFile)) {
        fs.unlinkSync(binFile);
      }
    } catch (e) {
      results.push({
        name: testCase.name,
        description: testCase.metadata.description,
        passed: false,
        error: String(e)
      });
    }
  }
  
  return results;
}

// ============================================================================
// Reporting
// ============================================================================

function printResults(results: TestResult[]): void {
  const passed = results.filter(r => r.passed).length;
  const failed = results.filter(r => !r.passed).length;
  
  console.log('\n' + '='.repeat(70));
  console.log('TEST RESULTS\n');
  
  for (const result of results) {
    const symbol = result.passed ? '✅' : '❌';
    console.log(`${symbol} ${result.name}`);
    console.log(`   ${result.description}`);
    
    if (!result.passed) {
      if (result.error) {
        console.log(`   Error: ${result.error}`);
      }
      if (result.expected) {
        console.log(`   Expected: ${JSON.stringify(result.expected)}`);
      }
      if (result.actual) {
        console.log(`   Actual: ${JSON.stringify(result.actual)}`);
      }
    }
    console.log();
  }
  
  console.log('='.repeat(70));
  console.log(`\n${passed} passed, ${failed} failed out of ${results.length} tests\n`);
  
  if (failed > 0) {
    process.exit(1);
  }
}

// ============================================================================
// Entry Point
// ============================================================================

async function main() {
  const casesDir = process.argv[2] || path.join(__dirname, 'cases');
  
  console.log(`Running fasm68k tests from: ${casesDir}\n`);
  
  const results = await runAllTests(casesDir);
  printResults(results);
}

main().catch(e => {
  console.error('Fatal error:', e);
  process.exit(1);
});

