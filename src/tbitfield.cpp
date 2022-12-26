// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0)
        throw "Error";
    BitLen = len;
    MemLen = BitLen / (sizeof(int) * 8) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
    BitLen = 0;
    MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / (sizeof(int) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM mask = 1 << (n % (sizeof(int) * 8));
    return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen))
        throw "Error";
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen))
        throw "Error";
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen))
        throw "Error";
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0 ? 0 : 1);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        if (pMem != NULL)
        {
            delete[]pMem;
            pMem = new TELEM[MemLen];
        }
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    else
    {
        for (int i = 0; i < MemLen; i++)
        {
            if (pMem[i] != bf.pMem[i])
                return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 1;
    else
    {
        for (int i = 0; i < MemLen; i++)
        {
            if (pMem[i] != bf.pMem[i])
                return 1;
        }
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int MaxLen = BitLen > bf.BitLen ? BitLen : bf.BitLen;
    TBitField tmp(MaxLen);
    for (int i = 0; i < MemLen; i++)
    {
        tmp.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++)
    {
        tmp.pMem[i] |= bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int MaxLen = BitLen > bf.BitLen ? BitLen : bf.BitLen;
    TBitField tmp(MaxLen);
    for (int i = 0; i < MemLen; i++)
    {
        tmp.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++)
    {
        tmp.pMem[i] &= bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    for (int i = 0; i < BitLen; i++)
    {
        pMem[GetMemIndex(i)] ^= GetMemMask(i);
    }
    return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char k;
    for (int i = 0; i < bf.GetLength(); ++i)
    {
        istr >> k;
        if (k == '1')
        {
            bf.SetBit(i);
        }
        else
        {
            if (k == '0')
            {
                bf.ClrBit(i);
            }
            else break;
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.GetLength() - 1; i >= 0; --i)
    {
        ostr << bf.GetBit(i) << ' ';
    }
    ostr << endl;
    return ostr;
}
