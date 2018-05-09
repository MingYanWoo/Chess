#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    Stone _s[32];
    int _r;             // stone radius
    int _selectid;      // selected stone id
    bool _bRedTurn;     // which turn

    // return a QPoint of stone's position
    QPoint center(int row, int col);
    QPoint center(int id);

    // darw stone
    void drawStone(QPainter &painter, int id);
    // return row and col from position
    bool getRowCol(QPoint pt, int &row, int &col);

    // move rule
    bool canMove(int moveid, int row, int col, int killid);
    bool canMoveJIANG(int moveid, int row, int col, int killid);
    bool canMoveCHE(int moveid, int row, int col, int killid);
    bool canMovePAO(int moveid, int row, int col, int killid);
    bool canMoveMA(int moveid, int row, int col, int killid);
    bool canMoveBING(int moveid, int row, int col, int killid);
    bool canMoveSHI(int moveid, int row, int col, int killid);
    bool canMoveXIANG(int moveid, int row, int col, int killid);

    virtual void paintEvent(QPaintEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:
};

#endif // BOARD_H
