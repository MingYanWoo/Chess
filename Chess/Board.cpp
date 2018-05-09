#include "Board.h"
#include <QPainter>
#include <QMouseEvent>
#include <iostream>

Board::Board(QWidget *parent) : QWidget(parent)
{
    for(int i = 0; i < 32; ++i)
    {
        _s[i].init(i);
    }
    _selectid = -1;
    _bRedTurn = true;
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int d = 40;
    _r = d/2;

    // draw board
    for(int i = 1; i <= 10; ++i)
    {
        painter.drawLine(QPoint(d, i*d), QPoint(9*d, i*d));
    }
    for(int i = 1; i <= 9; ++i)
    {
        if(i == 1 || i == 9)
        {
            painter.drawLine(QPoint(i*d, d), QPoint(i*d, 10*d));
        }
        else
        {
            painter.drawLine(QPoint(i*d, d), QPoint(i*d, 5*d));
            painter.drawLine(QPoint(i*d, 6*d), QPoint(i*d, 10*d));
        }
    }
    painter.drawLine(QPoint(4*d, d), QPoint(6*d, 3*d));
    painter.drawLine(QPoint(6*d, d), QPoint(4*d, 3*d));
    painter.drawLine(QPoint(4*d, 8*d), QPoint(6*d, 10*d));
    painter.drawLine(QPoint(6*d, 8*d), QPoint(4*d, 10*d));

    // draw stone
    for(int i = 0; i < 32; ++i)
    {
        drawStone(painter, i);
    }
}

QPoint Board::center(int row, int col)
{
    QPoint ret;
    ret.rx() = (col+1)*_r*2;
    ret.ry() = (row+1)*_r*2;
    return ret;
}

QPoint Board::center(int id)
{
    return center(_s[id]._row, _s[id]._col);
}

void Board::drawStone(QPainter &painter, int id)
{
    if(_s[id]._dead)
    {
        return;
    }
    QPoint c = center(id);
    QRect rect = QRect(c.x()-_r, c.y()-_r, _r*2, _r*2);

    if(id == _selectid)
    {
        painter.setBrush(QBrush(Qt::lightGray));
    }
    else
    {
        painter.setBrush(QBrush(Qt::yellow));
    }
    painter.setPen(Qt::black);

    painter.drawEllipse(center(id), _r, _r);

    if(_s[id]._red)
    {
        painter.setPen(Qt::red);
    }
    painter.setFont(QFont("system", _r, 700));

    painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));
}

bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row = 0; row <= 9; ++row)
    {
        for(col = 0; col <= 8; ++col)
        {
            QPoint c = center(row, col);
            int dx = c.x() - pt.x();
            int dy = c.y() - pt.y();
            int dist = dx*dx+dy*dy;
            if(dist < _r*_r)
                return true;
        }
    }
    return false;
}

void Board::mouseReleaseEvent(QMouseEvent *env)
{
    QPoint pt = env->pos();
    // get row and col from clicked position
    int row, col;
    bool bRet = getRowCol(pt, row, col);
    if(bRet == false)
        return;         // click outsides return

    int clickid = -1;
    int i;
    for(i = 0; i < 32; ++i)
    {
        if(_s[i]._row == row && _s[i]._col == col && _s[i]._dead == false)
        {
                break;
        }
    }

    if(i < 32)
    {
        clickid = i;
    }

    if(_selectid == -1)
    {
        if(clickid != -1)
        {
            if(_bRedTurn == _s[clickid]._red)
            {
                _selectid = clickid;
                update();
            }
        }
    }
    else
    {
        std::cout << clickid << std::endl;
        if(canMove(_selectid, row, col, clickid))
        {
            _s[_selectid]._row = row;
            _s[_selectid]._col = col;
            if(clickid != -1)
            {
                _s[clickid]._dead = true;
            }
            _selectid = -1;
            _bRedTurn = !_bRedTurn;
            update();
        }
    }

}

bool Board::canMove(int moveid, int row, int col, int killid)
{
    if(_s[moveid]._red == _s[killid]._red)
    {
        _selectid = killid;
        update();
        return false;
    }

    switch (_s[moveid]._type)
    {
    case Stone::JIANG:
        return canMoveJIANG(moveid, row, col, killid);
        break;
    case Stone::SHI:
        return canMoveSHI(moveid, row, col, killid);
        break;
    case Stone::CHE:
        return canMoveCHE(moveid, row, col, killid);
        break;
    case Stone::PAO:
        return canMovePAO(moveid, row, col, killid);
        break;
    case Stone::MA:
        return canMoveMA(moveid, row, col, killid);
        break;
    case Stone::BING:
        return canMoveBING(moveid, row, col, killid);
        break;
    case Stone::XIANG:
        return canMoveXIANG(moveid, row, col, killid);
        break;
    default:
        break;
    }
    return true;
}

bool Board::canMoveJIANG(int moveid, int row, int col, int killid)
{
    if(_s[moveid]._red)
    {
        if(row > 2) return false;
    }
    else
    {
        if(row < 7) return false;
    }
    if(col < 3) return false;
    if(col > 5) return false;

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc);
    if(d == 1 || d == 10)
        return true;

    return false;
}
bool Board::canMoveCHE(int moveid, int row, int col, int killid)
{
    return true;
}
bool Board::canMovePAO(int moveid, int row, int col, int killid)
{
    return true;
}
bool Board::canMoveMA(int moveid, int row, int col, int killid)
{
    return true;
}
bool Board::canMoveBING(int moveid, int row, int col, int killid)
{
    return true;
}
bool Board::canMoveSHI(int moveid, int row, int col, int killid)
{
    return true;
}
bool Board::canMoveXIANG(int moveid, int row, int col, int killid)
{
    return true;
}

