ENTRY(entrypoint);

ASSERT ((_bootSegmentRomEnd <= 0x101000), "Error: _bootSegmentRomEnd is larger than 1 MB");

// TODO: This should be checking for an address a lot earlier than this one.
ASSERT ((_buffersSegmentEnd < 0x80780000), "Error: The game is overflowing the RAM limit for non-overlay segments.");
ASSERT ((_framebuffer_hiSegmentStart == 0x80780000), "Error: framebuffer_hi shifted?");
