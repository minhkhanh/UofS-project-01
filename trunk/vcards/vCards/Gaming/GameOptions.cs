using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    //public enum AILevel
    //{
    //    Min,
    //    Easy,
    //    Hard,
    //    Max
    //}

    public class GameOptions
    {
        bool sound = true;

        public bool Sound
        {
            get { return sound; }
            set { sound = value; }
        }

        int numAI = 1;

        public int PlayerNumber
        {
            get { return numAI; }
            set { numAI = value; }
        }

        List<string> strNameAI = new List<string>();
        public List<string> ArrNameAI
        {
            get { return strNameAI; }
            set { strNameAI = value; }
        }
        public GameOptions()
        {
            strNameAI.Add("Solar AI");
        }
        //AILevel level = AILevel.Easy;
        //public AILevel Level
        //{
        //    get { return level; }
        //    set { level = value; }
        //}

        //public string AILevelName()
        //{
        //    switch (level)
        //    {
        //        case AILevel.Easy:
        //        return "Easy";
        //        case AILevel.Hard:
        //        return "Hard";
        //        default:
        //        return "";
        //    }
        //}

        //public void IncreasePlayerNum()
        //{
        //    ++numAI;
        //    if (numAI > 4)
        //        numAI = 1;
        //}

        //public void DecreasePlayerNum()
        //{
        //    --numAI;
        //    if (numAI < 1)
        //        numAI = 4;
        //}

        //public void IncreaseAILevel()
        //{
        //    ++level;

        //    if (level == AILevel.Max)
        //        level = AILevel.Min + 1;
        //}

        //public void DecreaseAILevel()
        //{
        //    --level;

        //    if (level == AILevel.Min)
        //        level = AILevel.Max - 1;
        //}
    }
}
