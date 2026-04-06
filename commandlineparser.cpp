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
#include "constants_cli.h"
#include <QHash>
#include <QDebug>

namespace {

// OPTION_TABLE を QString 化して高速検索できるようにする
static const QHash<QString, const Constants::CliOption*>& optionMap()
{
    static const QHash<QString, const Constants::CliOption*> map = []{
        QHash<QString, const Constants::CliOption*> m;
        for (int i = 0; i < Constants::getOptionTableCount(); ++i) {
            const auto& opt = Constants::OPTION_TABLE[i];
            // OPTION_TABLE の name は UTF-8 とみなす
            m.insert(QString::fromUtf8(opt.name), &opt);
        }
        return m;
    }();
    return map;
}

} // namespace


SimpleCliOptions CommandLineParser::parseSimple(int argc, char* argv[])
{
    SimpleCliOptions opts;

    for (int i = 1; i < argc; ++i) {
        // Windows の argv は ANSI（CP932）なので Local8Bit
        QString arg = QString::fromLocal8Bit(argv[i]).trimmed();
        if (arg == "-nogui" || arg == "--nogui") {
            opts.nogui = true;
        }
    }
    return opts;
}


CliOptions CommandLineParser::parse(int argc, char* argv[])
{
    CliOptions opts;

    for (int i = 1; i < argc; ++i) {
        // Windows の argv は ANSI（CP932）なので Local8Bit
        QString arg = QString::fromLocal8Bit(argv[i]).trimmed();
    qDebug() << "--- MATCH TEST ---";
    for (auto it = optionMap().begin(); it != optionMap().end(); ++it) {
        qDebug() << "TABLE:" << "[" << it.key() << "]";
    }
    qDebug() << "INPUT:" << "[" << arg << "]";
        // OPTION_TABLE の name は UTF-8 とみなす
        const Constants::CliOption* opt = optionMap().value(arg, nullptr);

        // 2. 見つからず、かつ "--" で始まっている場合、ハイフン1つにして再検索
        if (!opt && arg.startsWith("--")) {
            QString normalizedArg = arg.mid(1).trimmed(); // "--m" -> "-m"
            opt = optionMap().value(normalizedArg, nullptr);
        }

        if (!opt) {
            if (!arg.startsWith("-")) {
                opts.programIds.push_back(arg);
            }
            continue;
        }

        // keyOption は UTF-8 とみなす
        QString key = QString::fromUtf8(opt->keyOption);

        // -nogui は main の分岐にも使うので特別扱い
        if (key == QString::fromUtf8(Constants::KEY_NOGUI)) {
            opts.nogui = true;
        }

        if (opt->requiresValue) {
            if (i + 1 < argc) {
                QString value = QString::fromLocal8Bit(argv[++i]).trimmed();
                opts.valueOptions[key] = value;
            }
        } else {
            opts.enabledFlags.insert(key);
        }
    }

    return opts;
}

