# Notes

`parse_operand` must be run on all operands before any byte is emitted! The
reason for this has to do with pc-relative addressing modes.

`move` and `movea` are actually encoded exactly the same way, so one might ask why
the `movea` mnemonic even exists, there seems to me to be zero reason.
Contrast this with the difference between `or` and `ori` which have different
encodings.
