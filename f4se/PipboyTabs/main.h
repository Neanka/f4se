#pragma once

#include "Shared.h"
#include "gfxfunctions.h"
#include "papfunctions.h"

void fillSkills();

void fillAvifsPages();

void Populate_entry(GFxValue * dst, GFxMovieRoot * root, TESForm * form1, TESForm * form2, int filter, std::vector<std::string> stringValue, float maxVal);

/*void Populate_GLOB_FORM_Pair(GFxValue * dst, GFxMovieRoot * root, TESGlobal * glob, TESForm * form, int filter, std::vector<std::string>stringValue);

void Populate_MESG_FORM_Pair(GFxValue * dst, GFxMovieRoot * root, BGSMessage * msg, TESForm * form, int filter, std::vector<std::string> stringValue);

void Populate_BOOK_FORM_Pair(GFxValue * dst, GFxMovieRoot * root, TESObjectBOOK * book, TESForm * form, int filter, std::vector<std::string> stringValue);
*/
void PopulateSkillEntry(GFxValue * dst, GFxMovieRoot * root, ActorValueInfo * baseSkill, int filter, std::vector<std::string> stringValue);
