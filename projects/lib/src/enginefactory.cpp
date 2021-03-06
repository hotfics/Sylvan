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

#include "enginefactory.h"
#include "uciengine.h"
#include "ucciengine.h"

REGISTER_ENGINE_CLASS(UciEngine, "UCI")
REGISTER_ENGINE_CLASS(UcciEngine, "UCCI")

ClassRegistry<ChessEngine>* EngineFactory::registry()
{
    static ClassRegistry<ChessEngine>* registry = new ClassRegistry<ChessEngine>;
    return registry;
}

ChessEngine* EngineFactory::create(const QString& protocol)
{
    return registry()->create(protocol);
}

QStringList EngineFactory::protocols()
{
    return registry()->items().keys();
}
