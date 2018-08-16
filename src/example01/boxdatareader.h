#ifndef BOXDATAREADER_H
#define BOXDATAREADER_H

#include <QBoxSet>
#include <QTextStream>

QT_CHARTS_USE_NAMESPACE

class BoxDataReader : public QTextStream {
 public:
  explicit BoxDataReader(QIODevice *device);
  QBoxSet *readBox();
  void readFile(QIODevice *device);

 protected:
  qreal findMedian(int begin, int end);

 private:
  QList<qreal> sortedList;
};

#endif  // BOXDATAREADER_H
