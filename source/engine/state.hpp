#ifndef STATE_HPP
#define STATE_HPP

#ifndef ARM9
#define ARM9
#endif

class SamplerState
{
  public:
  enum class State
  {
    PLAY,
    CHOP,
    SETTINGS
  };

  void updateDisplay();
  private:
};

#endif
