/*
	Copyright (C) 2009–2014 jakago
	Copyright (C) 2018–2026 CSReviser Team

	This file is part of CaptureStream2, a recorder that supports HLS for 
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

#include "commandlineparser.h"
#include "constants.h"
#include <QString>

RecordingConfig CommandLineParser::parse(int argc, char* argv[])
{
    RecordingConfig cfg;

    auto findOption = [&](const QString& arg) -> const Constants::CliOption* {
        for (int i = 0; i < Constants::OPTION_TABLE_COUNT; ++i) {
            if (arg == Constants::OPTION_TABLE[i].name)
                return &Constants::OPTION_TABLE[i];
        }
        return nullptr;
    };

    for (int i = 1; i < argc; ++i) {
        QString arg = argv[i];
        const Constants::CliOption* opt = findOption(arg);

        if (!opt) {
            cfg.programIds.push_back(arg);
            continue;
        }

        if (opt->requiresValue) {
            if (i + 1 >= argc)
                break;

            QString value = argv[++i];

            if (arg == "-t")      cfg.titleTagFormat = value;
            else if (arg == "-f") cfg.fileNameFormat = value;
            else if (arg == "-o") cfg.outputFolder = value;
            else if (arg == "-e") cfg.extension = value;
        }
        else {
            if (arg == "-nogui") cfg.nogui = true;
            else if (arg == "-z") cfg.optionZ = true;
            else if (arg == "-b") cfg.optionB = true;
            else if (arg == "-s") cfg.optionS = true;
        }
    }

    if (!cfg.hasProgramIds()) {
        cfg.titleTagFormat.reset();
        cfg.fileNameFormat.reset();
        cfg.outputFolder.reset();
        cfg.extension.reset();
        cfg.optionS = false;
    }

    return cfg;
}
