// GNU General Public License Agreement
// Copyright (C) 2015-2016 Daniele Berto daniele.fratello@gmail.com
//
// spacefab is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software Foundation.
// You must retain a copy of this licence in all copies.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details.
// ---------------------------------------------------------------------------------

#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent) :
    QLabel(parent)
{

}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
