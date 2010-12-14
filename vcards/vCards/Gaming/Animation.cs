//--------------------------------------------------------------------- 
//  This file is part of the Microsoft .NET Framework SDK Code Samples. 
//  
//  Copyright (C) Microsoft Corporation.  All rights reserved. 
//  
//This source code is intended only as a supplement to Microsoft 
//Development Tools and/or on-line documentation.  See these other 
//materials for detailed information regarding Microsoft code samples. 
//  
//THIS CODE AND INFORMATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY 
//KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
//IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
//PARTICULAR PURPOSE. 
//--------------------------------------------------------------------- 

using System;
using System.IO;
using System.Drawing;
using System.Diagnostics;

namespace vCards
{
    ///  
    /// Summary description for Animation. 
    ///  
    public abstract class Animation : IDisposable
    {
        ///  
        /// Specifies that no one-shot is playing. 
        ///  
        const float InvalidOneShotIndex = -1.0F;

        ///  
        /// Width of an individual animation cell. 
        ///  
        public int CellWidth { get { return cellWidthValue; } }
        int cellWidthValue;

        ///  
        /// Height of an individual animation cell. 
        ///  
        public int CellHeight { get { return cellHeightValue; } }
        int cellHeightValue;

        ///  
        /// Number of cell rows in the bitmap. 
        ///  
        int numberRows;

        ///  
        /// Number of cell columns in the bitmap. 
        ///  
        int numberColumns;

        /////  
        ///// Bitmap to be used for animating. 
        /////  
        //public IBitmap IBmpImage { get { return ibmpImage; } }
        //IBitmap ibmpImage;

        ///  
        /// Index of the animation cell currently being displayed.  This 
        /// index is specified within the context of the current cycle 
        /// (between the start and end cells), not the absolute cell within 
        /// the entire animation image. 
        ///  
        public int CurCell
        {
            get
            {
                if (curOneShotCell == InvalidOneShotIndex)
                    return (int)(curCellValue - startCell);

                return (int)(curOneShotCell - oneShotStartCell);

            }

            set
            {
                if (curOneShotCell == InvalidOneShotIndex)
                    curCellValue = (float)value + startCell;
                else
                    curOneShotCell = (float)value + oneShotStartCell;
            }
        }
        float curCellValue;

        ///  
        /// Gets the maximum number of cells in the animation. 
        ///  
        public int NumberCells { get { return numberColumns * numberRows; } }

        ///  
        /// Gets/Sets the rate of the animation in cells per second. 
        ///  
        public int AnimationRate
        {
            get
            {
                if (curOneShotCell == InvalidOneShotIndex)
                    return (int)cellsPerSecond;

                return (int)oneShotCellsPerSecond;
            }
            set
            {
                if (curOneShotCell == InvalidOneShotIndex)
                    cellsPerSecond = (float)value;
                else
                    oneShotCellsPerSecond = (float)value;
            }
        }
        float cellsPerSecond;

        ///  
        /// Cached rectangle representing the drawing bounds of the current 
        /// cell. 
        ///  
        internal Rectangle Region { get { return sourceRegion; } }
        Rectangle sourceRegion = new Rectangle(0, 0, 0, 0);

        ///  
        /// Keep track of whether the Bitmap used by this animation was 
        /// allocated or not. 
        ///  
        protected bool allocated = false;

        ///// <summary>
        ///// true: ibitmap
        ///// false: iimage
        ///// </summary>
        //bool imgKind;
        //public bool ImageKind
        //{
        //    get { return imgKind; }
        //}

        ///  
        /// Specifies whether the animation has been properly initialized or 
        /// not. 
        ///  
        public bool Init { get { return initialized; } }
        protected bool initialized = false;

        ///  
        /// Index of the first cell in the animation cycle. 
        ///  
        float startCell;

        ///  
        /// Index of the last cell in the animation cycle. 
        ///  
        float endCell;

        ///  
        /// Index of the first cell in a one-shot animation cycle. 
        /// After a one-shot is complete, it defaults back to the 
        /// regular cycle. 
        ///  
        float oneShotStartCell;

        ///  
        /// Index of the last cell in a one-shot animation cycle. 
        /// After a one-shot is complete, it defaults back to the 
        /// regular cycle. 
        ///  
        float oneShotEndCell;

        ///  
        /// Rate of one-shot animation in cells per second. 
        ///  
        float oneShotCellsPerSecond;

        ///  
        /// Index of cell currently being played on a one-shot 
        /// animation.  If set to InvalidOneShotIndex then 
        /// no one-shot is playing. 
        ///  
        float curOneShotCell = InvalidOneShotIndex;

        ///  
        /// Used to determine if a one-shot has finished. 
        ///  
        public bool Done
        {
            get
            {
                return curOneShotCell ==
                    InvalidOneShotIndex;
            }
        }

        //Animation(IBitmap ibmp, IGraphics graphics, int numberRows,
        //    int numberColumns, int startCell, int cellWidth, int cellHeight,
        //    int cellsPerSecond)
        //{
        //    initialized = false;

        //    // Initialize the cell information 
        //    this.cellWidthValue = cellWidth;
        //    this.cellHeightValue = cellHeight;
        //    this.numberRows = numberRows;
        //    this.numberColumns = numberColumns;

        //    startCell = 0;
        //    endCell = numberRows * numberColumns - 1;

        //    // Load and initialize the Bitmap object 

        //    ibmpImage = ibmp;//? graphics.CreateBitmap(ibmp, true);
        //    if (ibmpImage == null)
        //    {
        //        initialized = false;
        //        return;
        //    }

        //    allocated = true;
        //    imgKind = true;

        //    // Initialize timing information 
        //    this.cellsPerSecond = (float)cellsPerSecond;

        //    // Initialize the draw region rectangle 
        //    sourceRegion.Width = cellWidth;
        //    sourceRegion.Height = cellHeight;

        //    // Validate information for drawing the first cell 
        //    Update(0.0F);

        //    initialized = true;
        //}

        //Animation(IImage iimg, IGraphics graphics, int numberRows,
        //    int numberColumns, int startCell, int cellWidth, int cellHeight,
        //    int cellsPerSecond)
        //{
        //    initialized = false;

        //    // Initialize the cell information 
        //    this.cellWidthValue = cellWidth;
        //    this.cellHeightValue = cellHeight;
        //    this.numberRows = numberRows;
        //    this.numberColumns = numberColumns;

        //    startCell = 0;
        //    endCell = numberRows * numberColumns - 1;

        //    // Load and initialize the Bitmap object 
        //    //IBitmap ibmp = (IBitmap)iimg;
        //    iimgImage = iimg;//? graphics.CreateBitmap(ibmp, true);

        //    if (iimgImage == null)
        //    {
        //        initialized = false;
        //        return;
        //    }

        //    allocated = true;
        //    imgKind = false;

        //    // Initialize timing information 
        //    this.cellsPerSecond = (float)cellsPerSecond;

        //    // Initialize the draw region rectangle 
        //    sourceRegion.Width = cellWidth;
        //    sourceRegion.Height = cellHeight;

        //    // Validate information for drawing the first cell 
        //    Update(0.0F);

        //    initialized = true;
        //}

        //public Animation(Stream strm, IGraphics graphics, int numberRows,
        //    int numberColumns, int startCell, int cellWidth, int cellHeight,
        //    int cellsPerSecond)
        //{
        //    initialized = false;

        //    // Initialize the cell information 
        //    this.cellWidthValue = cellWidth;
        //    this.cellHeightValue = cellHeight;
        //    this.numberRows = numberRows;
        //    this.numberColumns = numberColumns;

        //    startCell = 0;
        //    endCell = numberRows * numberColumns - 1;

        //    // Load and initialize the Bitmap object 
        //    ibmpImage = graphics.CreateBitmap(strm, true);
        //    if (ibmpImage == null)
        //    {
        //        initialized = false;
        //        return;
        //    }

        //    allocated = true;
        //    imgKind = true;

        //    // Initialize timing information 
        //    this.cellsPerSecond = (float)cellsPerSecond;

        //    // Initialize the draw region rectangle 
        //    sourceRegion.Width = cellWidth;
        //    sourceRegion.Height = cellHeight;

        //    // Validate information for drawing the first cell 
        //    Update(0.0F);

        //    initialized = true;
        //}

        public Animation()
        {
        }

        ///  
        /// Create an animation from a Bitmap stream. 
        ///  
        /// Stream representing source bitmap 
        /// Graphics object, needed for bitmap loading 
        ///  
        /// Number of rows of cells in the animation 
        ///  
        /// Number of columns of cells in the 
        /// animation 
        /// Index from which to start animating 
        ///  
        /// Width of individual animation cells 
        ///  
        /// Height of individual animation cells 
        ///  
        /// Rate of animation in cells per 
        /// second 
        /// The time that this animation started 
        /// animating in milliseconds 
        public Animation(int numberRows, int numberColumns,
            int startCell, int cellWidth, int cellHeight,
            int cellsPerSecond)
        {
            initialized = false;

            // Initialize the cell information 
            this.cellWidthValue = cellWidth;
            this.cellHeightValue = cellHeight;
            this.numberRows = numberRows;
            this.numberColumns = numberColumns;

            startCell = 0;
            endCell = numberRows * numberColumns - 1;

            // Initialize timing information 
            this.cellsPerSecond = (float)cellsPerSecond;

            // Initialize the draw region rectangle 
            sourceRegion.Width = cellWidth;
            sourceRegion.Height = cellHeight;

            // Validate information for drawing the first cell 
            Update(0.0F);

            initialized = true;
        }

        ///  
        /// Create an animation that shares information from another 
        /// animation. 
        ///  
        /// Original Animation object 
        /// Index from which to start animating 
        ///  
        /// Rate of animation in cells per 
        /// second 
        /// The time that this animation started 
        /// animating in milliseconds 
        //public Animation(Animation animation, int startCell,
        //    int cellsPerSecond)
        //{
        //    initialized = false;

        //    // Initialize the cell information 
        //    cellWidthValue = animation.cellWidthValue;
        //    cellHeightValue = animation.cellHeightValue;
        //    numberRows = animation.numberRows;
        //    numberColumns = animation.numberColumns;

        //    this.startCell = 0;
        //    endCell = numberRows * numberColumns - 1;

        //    //// Copy the reference to the original bitmap 
        //    //ibmpImage = animation.ibmpImage;
        //    //if (ibmpImage == null)
        //    //{
        //    //    initialized = false;
        //    //    return;
        //    //}

        //    //allocated = false;
        //    //imgKind = true;

        //    // Initialize timing information 
        //    this.cellsPerSecond = (float)cellsPerSecond;

        //    // Initialize the draw region rectangle 
        //    sourceRegion.Width = cellWidthValue;
        //    sourceRegion.Height = cellHeightValue;

        //    // Validate information for drawing the first cell 
        //    Update(0.0F);

        //    initialized = true;
        //}

        ///  
        /// Set the start and end cells of the current animation cycle.  All 
        /// cells will be played sequentially within the cycle. 
        ///  
        /// Index of starting cell 
        /// Index of ending cell 
        public void SetCycle(int startCell, int endCell, int animationRate)
        {
            curOneShotCell = InvalidOneShotIndex;
            this.startCell = (float)startCell;
            this.endCell = (float)endCell;
            cellsPerSecond = animationRate;
            curCellValue = startCell;
        }

        ///  
        /// Start a one shot animation cycle.  This cycle will interrupt the 
        /// current cycle, then resume the current cycle once finished. 
        ///  
        /// Index of start cell in cycle 
        /// Index of end cell in cycle 
        public void StartOneShot(int startCell, int endCell, int animationRate)
        {
            oneShotStartCell = (float)startCell;
            oneShotEndCell = (float)endCell;
            oneShotCellsPerSecond = (float)animationRate;
            curOneShotCell = oneShotStartCell;
        }

        void Update(ref bool cycleFinished, float deltaTime_s)
        {
            float deltaFrames = AnimationRate * deltaTime_s;

            // Animations look bad if frames are skipped even though the 
            // frame-rate might be too slow so don't allow it 
            if (deltaFrames > 1.0F)
                deltaFrames = 1.0F;

            int currentCell;

            if (InvalidOneShotIndex != curOneShotCell)
            {
                curOneShotCell += deltaFrames;
                if (curOneShotCell >= oneShotEndCell + 1.0F)
                {
                    curOneShotCell = InvalidOneShotIndex;
                    currentCell = (int)curCellValue;

                    cycleFinished = true;
                }
                else
                {
                    currentCell = (int)curOneShotCell;

                    cycleFinished = false;
                }
            }
            else
            {
                curCellValue += deltaFrames;
                if (curCellValue >= endCell + 1.0F)
                {
                    curCellValue = startCell;

                    cycleFinished = true;
                }
                else
                    cycleFinished = false;

                currentCell = (int)curCellValue;
            }

            Debug.Assert(numberColumns > 0,
                "Animation.Update: Invalid number of columns specified");

            // Set up the draw region rectangle for the current cell 
            sourceRegion.X = (int)((currentCell % numberColumns) * cellWidthValue);
            sourceRegion.Y = (int)((currentCell / numberColumns) * cellHeightValue);
        }

        ///  
        /// Update the animation cell information. 
        ///  
        /// Current system time in milliseconds. 
        ///  
        public void Update(float deltaTime_s)
        {
            float deltaFrames = AnimationRate * deltaTime_s;

            // Animations look bad if frames are skipped even though the 
            // frame-rate might be too slow so don't allow it 
            if (deltaFrames > 1.0F)
                deltaFrames = 1.0F;

            int currentCell;

            if (InvalidOneShotIndex != curOneShotCell)
            {
                curOneShotCell += deltaFrames;
                if (curOneShotCell >= oneShotEndCell + 1.0F)
                {
                    curOneShotCell = InvalidOneShotIndex;
                    currentCell = (int)curCellValue;
                }
                else
                {
                    currentCell = (int)curOneShotCell;
                }
            }
            else
            {
                curCellValue += deltaFrames;
                if (curCellValue >= endCell + 1.0F)
                    curCellValue = startCell;

                currentCell = (int)curCellValue;
            }

            Debug.Assert(numberColumns > 0,
                "Animation.Update: Invalid number of columns specified");

            // Set up the draw region rectangle for the current cell 
            sourceRegion.X = (int)((currentCell % numberColumns) * cellWidthValue);
            sourceRegion.Y = (int)((currentCell / numberColumns) * cellHeightValue);
        }

        ///  
        /// Clean up any memory allocated by the bitmap object. 
        ///  
        virtual public void Dispose()
        {
            //if (!allocated)
            //    return;

            //if (ibmpImage != null)
            //    ibmpImage.Dispose();
        }

        //////////////////////////////////////////////////////////////////////////
        // added code:
        //////////////////////////////////////////////////////////////////////////

        public abstract void Draw(IGraphics igr, int x, int y, int w, int h);
        public abstract void Draw(IGraphics igr, int x, int y, Rectangle rectSrc);
        public abstract void Draw(IGraphics igr, int x, int y);

    }
}
