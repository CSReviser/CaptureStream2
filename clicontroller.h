/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2026 CSReviser Team

	This file is part of CaptureStream2, the recorder to support HLS for 
	NHK radio language courses.
	CaptureStream2 is a modified version of CaptureStream, originally 
	developed by jakago.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/gpl-2.0.html>.
*/

#pragma once
#include <QString>
#include "settings.h"
#include "runtimeconfig.h"

class CLIController {
public:
    CLIController(const Settings& settings, int argc, char** argv);
    int run();
    bool validateOptions(const CliOptions& opts) const;
    bool validateProgramIds(const CliOptions& opts) const;
    void applyCliOverrides(RuntimeConfig& config, const CliOptions& opts) const;
    
private:
    const Settings& m_settings;   // ← 参照にする
    int m_argc;
    char** m_argv;

    void showHelp();
    void testFfmpeg();

};
