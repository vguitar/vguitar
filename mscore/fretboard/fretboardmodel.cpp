#include "fretboardmodel.h"
#include <math.h>
#include <QDebug>

namespace vg
{
    QRect &FretboardModel::rect()
    {
        return fretboardRect;
    }

    void FretboardModel::setRect(const QRect &r)
    {
        fretboardRect = r;
        update();
    }
    
    QPoint FretboardModel::intersectionPoint(int fretNumber, int stringNumber)
    {
        Q_ASSERT(fretNumber >= 0 && fretNumber < numberOfFrets);
        Q_ASSERT(stringNumber >= 0 && stringNumber < numberOfStrings);
        
        float fretPos = posForFret(fretNumber);
        float stringPos = posForString(stringNumber);
        
        QPoint result = (orientation == Qt::Horizontal) ? QPoint(fretPos, stringPos) : QPoint(stringPos, fretPos);
        return result;
    }

    QRect FretboardModel::getFretRect(int fretNumber, int stringNumber)
    {
        Q_ASSERT(fretNumber > 0 && fretNumber < (int)fretPositions.size());
        Q_ASSERT(stringNumber > 0 && stringNumber < (int)stringPositions.size());
        
        QPoint start = intersectionPoint(fretNumber - 1, stringNumber - 1);
        QPoint end = start;
  
        if (stringNumber < numberOfStrings && fretNumber < numberOfFrets)
        {
            end = intersectionPoint(fretNumber, stringNumber);
        }
        
        return QRect(start, end);
    }

    float FretboardModel::widthForString(int stringIndex)
    {
        Q_ASSERT(stringIndex >= 0 && stringIndex < numberOfStrings);

        return (float)(stringIndex + 1) / (float)numberOfStrings;
    }

    void FretboardModel::update()
    {
        updateFretPositions();
        updateStringPositions();
    }

    void FretboardModel::updateStringPositions()
    {
        stringPositions.clear();

        int margin = 15;
        int fretboardWidth = orientation == Qt::Horizontal ? rect().height(): rect().width();
        fretboardWidth -= margin * 2;

        int stringSpacing = fretboardWidth / (numberOfStrings - 1);

        //Always compute the positions for one extra string
        for (auto i = 0; i <= numberOfStrings; i++)
        {
            float position = margin + i * stringSpacing;
            stringPositions.push_back(position);
        }
    }

    void FretboardModel::updateFretPositions()
    {
        float length = orientation == Qt::Horizontal ? rect().width() : rect().height();
        length -= nutThickness;

        auto& positions = fretPositions;
        positions.clear();
        positions.push_back(0);

        for (int n = 1; n <= numberOfFrets; n++)
        {
            float root2 = pow(1.05946, n);
            float pos = length - length / root2;
            pos += nutThickness;
            pos += fretThickness;
            positions.push_back(pos);
        }

        //Normalize positions
        float last = positions.back();

        std::transform(positions.begin(), positions.end(), positions.begin(), [last, length](float x){
            return (x / last) * length;
        });
    }
}
