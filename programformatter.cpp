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

#include "programformatter.h"
#include "programrepository.h"

QStringList ProgramFormatter::toLines(const QStringList& names)
{
    auto &repo = ProgramRepository::instance();

    QStringList lines;

 qsizetype maxWidth = 0;

for (const QString& name : names) {
    QString id = repo.name_map[name];
    maxWidth = std::max(maxWidth, id.length());
}

lines << QString("%1 : %2")
            .arg("番組ID", -int(maxWidth))
            .arg("番組名");

for (const QString& name : names) {
    QString id = repo.name_map[name];
    lines << QString("%1 : %2")
                 .arg(id, -int(maxWidth))
                 .arg(name);
}
    return lines;
}


