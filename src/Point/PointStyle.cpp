#include "PointStyle.h"
#include <qmath.h>

const int DEFAULT_POINT_RADIUS = 10;

PointStyle::PointStyle ()
{
}

PointStyle::PointStyle(PointShape pointShape,
                       unsigned int radius,
                       ColorPalette paletteColor) :
  m_pointShape (pointShape),
  m_radius (radius),
  m_paletteColor (paletteColor)
{
}

PointStyle::PointStyle (const PointStyle &other) :
  m_pointShape (other.pointShape()),
  m_radius (other.radius ()),
  m_paletteColor (other.paletteColor ())
{
}

PointStyle &PointStyle::operator=(const PointStyle &other)
{
  m_pointShape = other.pointShape ();
  m_radius = other.radius ();
  m_paletteColor = other.paletteColor ();

  return *this;
}

QColor PointStyle::color () const
{
  switch (m_paletteColor) {
    case COLOR_PALETTE_BLACK:
      return Qt::black;
      break;

    case COLOR_PALETTE_BLUE:
      return Qt::blue;
      break;

    case COLOR_PALETTE_CYAN:
      return Qt::cyan;
      break;

    case COLOR_PALETTE_GOLD:
      return QColor (0xff, 0xd7, 0x00);
      break;

    case COLOR_PALETTE_GREEN:
      return Qt::green;
      break;

    case COLOR_PALETTE_MAGENTA:
      return Qt::magenta;
      break;

    case COLOR_PALETTE_RED:
      return Qt::red;
      break;

    case COLOR_PALETTE_TRANSPARENT:
      return Qt::transparent;
      break;

    case COLOR_PALETTE_YELLOW:
      return Qt::yellow;
      break;

    default:
      Q_ASSERT (false);
  }
}

PointStyle PointStyle::defaultAxesCurve ()
{
  return PointStyle (POINT_SHAPE_CROSS,
                     DEFAULT_POINT_RADIUS,
                     COLOR_PALETTE_RED);
}

PointStyle PointStyle::defaultGraphCurve (int index)
{
  PointShape pointShape = POINT_SHAPE_CROSS;
  switch (index % 4) {
    case 0:
      pointShape = POINT_SHAPE_CROSS;
      break;

    case 1:
      pointShape = POINT_SHAPE_X;
      break;

    case 2:
      pointShape = POINT_SHAPE_DIAMOND;
      break;

    case 3:
      pointShape = POINT_SHAPE_SQUARE;
      break;

    default:
      Q_ASSERT (false);
  }

  return PointStyle (pointShape,
                     DEFAULT_POINT_RADIUS,
                     COLOR_PALETTE_BLUE);
}

bool PointStyle::isCircle () const
{
  return m_pointShape == POINT_SHAPE_CIRCLE;
}

ColorPalette PointStyle::paletteColor () const
{
  return m_paletteColor;
}

PointShape PointStyle::pointShape () const
{
  return m_pointShape;
}

QPolygonF PointStyle::polygon () const
{
  QVector<QPointF> points;

  switch (m_pointShape) {

    case POINT_SHAPE_CIRCLE:
      Q_ASSERT (false);
      break;

    case POINT_SHAPE_CROSS:
      {
        int component = m_radius;

        points.append (QPointF (-1 * component, 0));
        points.append (QPointF (component, 0));
        points.append (QPointF (0, 0));
        points.append (QPointF (0, component));
        points.append (QPointF (0, -1 * component));
        points.append (QPointF (0, 0));
      }
      break;

    case POINT_SHAPE_DIAMOND:
      {
        int component = m_radius;

        points.append (QPointF (0, -1 * component));
        points.append (QPointF (-1 * component, 0));
        points.append (QPointF (0, component));
        points.append (QPointF (component, 0));
      }
      break;

    case POINT_SHAPE_SQUARE:
      {
        int component = m_radius;

        points.append (QPointF (-1 * component, -1 * component));
        points.append (QPointF (-1 * component, component));
        points.append (QPointF (component, component));
        points.append (QPointF (component, -1 * component));
      }
      break;

    case POINT_SHAPE_TRIANGLE:
      {
        int component = m_radius;

        points.append (QPointF (-1 * component, -1 * component));
        points.append (QPointF (0, component));
        points.append (QPointF (component, -1 * component));
      }
      break;

    case POINT_SHAPE_X:
      {
        int component = m_radius * qSqrt (0.5);

        points.append (QPointF (-1 * component, -1 * component));
        points.append (QPointF (component, component));
        points.append (QPointF (0, 0));
        points.append (QPointF (-1 * component, component));
        points.append (QPointF (component, -1 * component));
        points.append (QPointF (0, 0));
      }
      break;

    default:
      Q_ASSERT (false);
  }

  QPolygonF polygon (points);
  return polygon;
}

int PointStyle::radius () const
{
  return m_radius;
}

void PointStyle::setPaletteColor (ColorPalette paletteColor)
{
  m_paletteColor = paletteColor;
}

void PointStyle::setRadius (int radius)
{
  m_radius = radius;
}