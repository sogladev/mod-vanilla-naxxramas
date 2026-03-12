#include "IndividualProgression.h"

// Simple implementation: default to false for progression flags
IndividualProgression::IndividualProgression() : doableNaxx40Bosses(false), requireNaxxStrath(false) { }

// Define the global pointer used by scripts
IndividualProgression g_IndividualProgression;
IndividualProgression* sIndividualProgression = &g_IndividualProgression;
