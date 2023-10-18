# Simple Tool for the Channel

These are listed in the order they are applied to the signal.
- Mono
- Stero Width
  This plays with the relative volumes of the mid and side. 
  As the value goes up, the side is boosted and the mids are lowered.
  At 200% side will be at double the original volume and the mids will be
  at zero. At 0%, the side will be at 0% and the mids will be at double the
  original volume. Obviously, this is the same as turnning on mono - but with
  a volume boost. Prefer to use mono instead since it takes less CPU power.
- Volume
- Channel Phase Invert
  - Note that this is done before the channel swap
  - However, it is done AFTER mono - so you can get a really wide
    signal by turning on mono and then inverting one side.
- Channel Swap
