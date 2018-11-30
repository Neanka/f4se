#pragma once
#include "Shared.h"

void ReadSettings();

void ApplySettings(GFxMovieRoot * movieRoot);

void ToggleReserveVisibility(UInt8 visible);

void TuneLinePosition(float newLineLength);

void TuneHorizontalPosition(float newLineX);

void TuneWidgetPosition(GFxMovieRoot * movieRoot);

void SetDefaultElementsPosition(GFxMovieRoot * movieRoot);

void SetHorizontalElementsPosition(GFxMovieRoot * movieRoot);
