/*
    This file is part of Sylvan.

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

#ifndef UCCIENGINE_H
#define UCCIENGINE_H

#include <QVarLengthArray>
#include "chessengine.h"

/*!
 * \brief A chess engine which uses the UCCI chess interface.
 *
 * UCCI's specifications: http://www.xqbase.com/protocol/cchess_ucci.htm
 */
class LIB_EXPORT UcciEngine : public ChessEngine
{
    Q_OBJECT

public:
    /*! Creates a new UcciEngine. */
    UcciEngine(QObject* parent = nullptr);

    // Inherited from ChessEngine
    virtual void endGame(const Chess::Result& result);
    virtual void makeMove(const Chess::Move& move);
    virtual void makeBookMove(const Chess::Move& move);
    virtual QString protocol() const;
    virtual void startPondering();
    virtual void clearPonderState();

protected:
    // Inherited from ChessEngine
    virtual bool sendPing();
    virtual void sendStop();
    virtual void sendQuit();
    virtual void startProtocol();
    virtual void startGame();
    virtual void startThinking();
    virtual void parseLine(const QString& line);
    virtual void sendOption(const QString& name, const QVariant& value);
    virtual bool isPondering() const;

private:
    enum PonderState
    {
        NotPondering,
        Pondering,
        PonderHit
    };

    static QStringRef parseUcciTokens(const QStringRef& first,
                                     const QString* types,
                                     int typeCount,
                                     QVarLengthArray<QStringRef>& tokens,
                                     int& type);
    void parseInfo(const QVarLengthArray<QStringRef>& tokens,
                   int type,
                   MoveEvaluation* eval);
    void parseInfo(const QStringRef& line);
    EngineOption* parseOption(const QStringRef& line);
    void addVariantsFromOption(const EngineOption* option);
    void setVariant(const QString& variant);
    QString positionString(bool position);
    void sendPosition();
    void setPonderMove(const QString& moveString);
    QString directPv(const QVarLengthArray<QStringRef>& tokens);
    QString sanPv(const QVarLengthArray<QStringRef>& tokens);

    QString m_variantOption;
    QString m_startFen;
    QString m_moveStrings;
    bool m_useDirectPv;
    // Write buffer for messages that will be flushed to the engine
    // after it sends a "bestmove"
    QStringList m_bmBuffer;
    bool m_sendOpponentsName;
    bool m_canPonder;
    bool m_useMillisec;
    PonderState m_ponderState;
    Chess::Move m_ponderMove;
    QString m_ponderMoveSan;
    int m_movesPondered;
    int m_ponderHits;
    bool m_ignoreThinking;
    bool m_rePing;
    MoveEvaluation m_currentEval;
    QStringList m_comboVariants;
};

#endif // UCCIENGINE_H
