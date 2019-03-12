#pragma once

// This file is adapted from f4se/Translation.h.

class BSScaleformTranslator;

namespace SSWTranslator
{
	void LoadTranslations(BSScaleformTranslator * translator);
	bool ParseTranslation(BSScaleformTranslator * translator, std::string modName, std::string langCode);
}
