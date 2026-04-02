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

#include "programresolver.h"
#include "programrepository.h"
#include <QtGlobal>

// ---------- 正規化（表記ゆれ吸収） ----------
QString ProgramResolver::normalize(const QString& s)
{
    QString t = s.trimmed();

    // 全角スペース → 半角
    t.replace(u'　', u' ');

    // 連続スペース圧縮
    t = t.simplified();

    return t;
}

// ---------- メイン解決 ----------
ResolveResult ProgramResolver::resolve(const QString& input)
{
    ResolveResult r;

    QString key = normalize(input);

    // 1文字入力は禁止（ノイズ防止）
    if (key.size() <= 1) {
        r.status = ResolveResult::NotFound;
        return r;
    }

    auto& repo = ProgramRepository::instance();

    int bestScore = 0;
    QStringList bestIds;

    // 2文字以上で部分一致を許可
    const int MIN_PARTIAL_TITLE_LENGTH = 2;
    const int MIN_PARTIAL_ID_LENGTH = 5;

    for (auto it = repo.name_map.cbegin(); it != repo.name_map.cend(); ++it) {

        const QString& title = it.key();
        const QString& id    = it.value();

        int score = 0;

        // ---- スコア評価 ----

        // 5: ID完全一致
        if (id == key) {
            score = 5;
        }
        // 4: タイトル完全一致
        else if (QString::compare(title, key, Qt::CaseInsensitive) == 0) {
            score = 4;
        }
        // 3: タイトル前方一致
        else if (title.startsWith(key, Qt::CaseInsensitive)) {
            score = 3;
        }
        // 2: タイトル任意部分一致
        else if (key.length() >= MIN_PARTIAL_TITLE_LENGTH &&
                 title.contains(key, Qt::CaseInsensitive)) {
            score = 2;
        }
        // 1: ID任意部分一致（最後の救済）
        else if (key.length() >= MIN_PARTIAL_ID_LENGTH &&
                 id.contains(key, Qt::CaseInsensitive)) {
            score = 1;
        }

        if (score == 0)
            continue;

        // ---- 最良候補更新 ----
        if (score > bestScore) {
            bestScore = score;
            bestIds.clear();
            bestIds << id;
        }
        else if (score == bestScore) {

            // 同点ならタイトル長が短いものを優先
            if (!bestIds.isEmpty()) {

                QString currentTitle = title;
                QString bestTitle    = repo.name_map.key(bestIds.first());

                if (currentTitle.length() < bestTitle.length()) {
                    bestIds.clear();
                    bestIds << id;
                }
                else if (currentTitle.length() == bestTitle.length()) {
                    bestIds << id;
                }
            }
            else {
                bestIds << id;
            }
        }
    }

    bestIds.removeDuplicates();

    // ---- 結果 ----
    if (bestIds.isEmpty()) {
        r.status = ResolveResult::NotFound;
    }
    else if (bestIds.size() == 1) {
        r.status = ResolveResult::Unique;
        r.id = bestIds.first();
    }
    else {
        r.status = ResolveResult::Ambiguous;
        r.candidates = bestIds;
    }

    return r;
}

// ---------- Unique専用ラッパ ----------
QString ProgramResolver::resolveUnique(const QString& input)
{
    auto r = resolve(input);
    return (r.status == ResolveResult::Unique) ? r.id : QString();
}




/*
#include "programresolver.h"
#include "programrepository.h"

QString ProgramResolver::normalize(const QString& s)
{
    QString t = s.trimmed();

    // 全角→半角対策など将来ここに追加可能
    return t;
}

ResolveResult ProgramResolver::resolve(const QString& input)
{
    ResolveResult r;
    if (input.isEmpty())
        return r;

    auto& repo = ProgramRepository::instance();
    QString key = normalize(input);

    int bestScore = 0;
    QStringList best;

    for (auto it = repo.name_map.cbegin(); it != repo.name_map.cend(); ++it) {

        const QString& title = it.key();
        const QString& id    = it.value();

        int score = 0;

        // 5: ID完全一致
        if (id == key)
            score = 5;

        // 4: タイトル完全一致
        else if (QString::compare(title, key, Qt::CaseInsensitive) == 0)
            score = 4;

        // 3: 前方一致
        else if (title.startsWith(key, Qt::CaseInsensitive))
            score = 3;

        // 2: タイトル部分一致
        else if (title.contains(key, Qt::CaseInsensitive))
            score = 2;

        // 1: ID部分一致
        else if (id.contains(key, Qt::CaseInsensitive))
            score = 1;

        if (score == 0)
            continue;

        if (score > bestScore) {
            bestScore = score;
            best.clear();
            best << id;
        }
        else if (score == bestScore) {
            best << id;
        }
    }

    if (best.isEmpty()) {
        r.status = ResolveResult::NotFound;
    }
    else if (best.size() == 1) {
        r.status = ResolveResult::Unique;
        r.id = best.first();
    }
    else {
        r.status = ResolveResult::Ambiguous;
        r.candidates = best;
    }

    return r;
}

QString ProgramResolver::resolveUnique(const QString& input)
{
    auto r = resolve(input);
    if (r.status == ResolveResult::Unique)
        return r.id;
    return {};
}
*/
