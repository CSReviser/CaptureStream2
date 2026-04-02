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

#include "programlistservice.h"
#include "programrepository.h"
#include "constants_programs.h"

namespace {

bool match(const QString& name,
           const char* keywords[],
           int count)
{
    QString exclude = QString::fromUtf8(Constants::PROGRAM_EXCLUDE_TAG);

    if (name.contains(exclude))
        return false;

    for (int i = 0; i < count; ++i) {
        QString key = QString::fromUtf8(keywords[i]);

        if (name.contains(key))
            return true;
    }

    return false;
}

bool matchEnglish(const QString& name)
{
    return match(name,
                 Constants::PROGRAM_KEYWORDS_ENGLISH,
                 Constants::PROGRAM_KEYWORDS_ENGLISH_COUNT);
}

bool matchOtherLanguages(const QString& name)
{
    return match(name,
                 Constants::PROGRAM_KEYWORDS_OTHER,
                 Constants::PROGRAM_KEYWORDS_OTHER_COUNT);
}

}
/*
QStringList ProgramListService::buildProgramList(int type)
{
    auto &repo = ProgramRepository::instance();

    QStringList allIds = repo.name_map.keys();
    QStringList result;

    switch (type) {

    case English:
        for (const QString& id : allIds) {
            QString name = repo.name_map[id];

            if (matchEnglish(name))
                result << id;   // ← IDを入れる
        }
        break;

    case OtherLanguages:
        for (const QString& id : allIds) {
            QString name = repo.name_map[id];

            if (matchOtherLanguages(name))
                result << id;
        }
        break;

    case All:
        result = allIds;
        break;
    }

    return result;
}
*/
QStringList ProgramListService::buildProgramList(int type)
{
    auto &repo = ProgramRepository::instance();

    QStringList allKeys = repo.name_map.keys();
    QStringList result;

    switch (type) {

    case English:
        for (const QString& name : allKeys) {
            if (matchEnglish(name))
                result << name;
        }
        break;

    case OtherLanguages:
        for (const QString& name : allKeys) {
            if (matchOtherLanguages(name))
                result << name;
        }
        break;

    case All:
        result = allKeys;
        break;
    }

    return result;
}

