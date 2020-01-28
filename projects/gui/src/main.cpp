/*
    This file is part of Sylvan.
    Copyright (C) 2008-2018 Cute Chess authors
    Copyright (C) 2019 Wilbert Lee

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Sylvan.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QLoggingCategory>
#include <QTextStream>
#include <QStringList>
#include <QMetaType>
#include <QTranslator>

#include <board/genericmove.h>
#include <board/move.h>
#include <board/side.h>
#include <board/result.h>
#include <moveevaluation.h>

#include "sylvanapp.h"

int main(int argc, char* argv[])
{
    // Register types for signal / slot connections
    qRegisterMetaType<Chess::GenericMove>("Chess::GenericMove");
    qRegisterMetaType<Chess::Move>("Chess::Move");
    qRegisterMetaType<Chess::Side>("Chess::Side");
    qRegisterMetaType<Chess::Result>("Chess::Result");
    qRegisterMetaType<MoveEvaluation>("MoveEvaluation");

    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    SylvanApplication app(argc, argv);
    QString dir = app.applicationDirPath() + "/" + "translations";

    QTranslator translator;
    translator.load(QLocale(), "qt", "_", dir/*"translations"*/, ".qm");
    app.installTranslator(&translator);

    app.newDefaultGame();
    return app.exec();
}
