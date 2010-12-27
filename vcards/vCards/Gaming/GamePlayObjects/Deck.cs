using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Collections;

namespace vCards
{
    public class Deck
    {
        List<CardValue> listCards = new List<CardValue>(52);

        public void Shuffle()
        {
            bool[] arrAssigned = new bool[52];
            for (CardRank rank = CardRank.Three; rank < CardRank.Duece; ++rank)
            {
                for (CardSuit suit = CardSuit.Spades; suit < CardSuit.Hearts; ++suit)
                {
                    Random rand = new Random();
                    bool found = false;
                    while (found == false)
                    {
                        int index = rand.Next(52);
                        if (arrAssigned[index] == false)
                        {
                            listCards[index] = new CardValue((CardRank)rank, (CardSuit)suit);
                            found = true;
                            arrAssigned[index] = true;
                        }
                    }
                }
            }
        }

        public void Deal(params CardPack[] packs)
        {
            for (int i = 0; i < packs.Count(); ++i)
            {

            }
        }

        //public void Draw(IGraphics igr)     // update vi tri truoc khi xuat
        //{
        //    foreach (Card lb in listCard)
        //    {
        //        lb.DrawBkgr(igr);
        //    }
        //}
        //public void UpdatePos()
        //{
        //    if (listCard.Count<=0)
        //    {
        //        return;
        //    }
        //    listCard.Sort();
        //    int denta = this.Region.Width - Card.iBaseWidth;
        //    int dentadef = Card.iMaxWidth * listCard.Count;
        //    int left = Region.Left;
        //    int width = Card.iMaxWidth;
        //    if (denta>dentadef)
        //    {
        //        float temp = denta - dentadef;
        //        temp /= 2;
        //        left += (int)temp;
        //    } 
        //    else
        //    {
        //        float f = denta / (listCard.Count - 1);
        //        width = (int)f;
        //    }            
        //    for (int i=0; i<listCard.Count; ++i)
        //    {
        //        Rectangle rect = new Rectangle(left + width * i, listCard[i].Region.Y, listCard[i].Region.Width, listCard[i].Region.Height);
        //        listCard[i].Region = rect;
        //    }
        //}

        //#region IDisposable Members

        //public override void Dispose()
        //{

        //}

        //#endregion
    }
}
