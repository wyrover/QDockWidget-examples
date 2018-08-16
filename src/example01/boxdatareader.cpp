#include "boxdatareader.h"

BoxDataReader::BoxDataReader(QIODevice *device) : QTextStream(device) {}

QBoxSet *BoxDataReader::readBox() {
  QString line = readLine();
  if (line.startsWith("#")) {
    return 0;
  }

  QStringList strList = line.split(" ", QString::SkipEmptyParts);

  sortedList.clear();
  for (int i = 1; i != strList.count(); ++i) {
    sortedList.append(strList.at(i).toDouble());
  }
  qSort(sortedList.begin(), sortedList.end());

  int count = sortedList.count();

  QBoxSet *box = new QBoxSet(strList.first());
  box->setValue(QBoxSet::LowerExtreme, sortedList.first());
  box->setValue(QBoxSet::UpperExtreme, sortedList.last());
  box->setValue(QBoxSet::Median, findMedian(0, count));
  box->setValue(QBoxSet::LowerQuartile, findMedian(0, count / 2));
  box->setValue(QBoxSet::UpperQuartile,
                findMedian(count / 2 + (count % 2), count));

  return box;
}

void BoxDataReader::readFile(QIODevice *device) {
  QTextStream::setDevice(device);
}

qreal BoxDataReader::findMedian(int begin, int end) {
  int count = end - begin;
  if (count % 2) {
    return sortedList.at(count / 2 + begin);
  } else {
    qreal right = sortedList.at(count / 2 + begin);
    qreal left = sortedList.at(count / 2 - 1 + begin);
    return (right + left) / 2.;
  }
}
