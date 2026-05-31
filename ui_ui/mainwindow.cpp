#include "mainwindow.h"
#include "resources.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include "exceptions.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QRegularExpression>

template <typename T>
T double_val(T x) { 
    return x * static_cast<T>(2); 
}

template <typename T>
bool is_big(T x) { 
    return x > static_cast<T>(60); 
}

template <typename T>
T sum_func(T acc, T x) { 
    return acc + x; 
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(APP_TITLE);
    resize(700, 800);
    setStyleSheet(mainStyle());

    tabs = new QTabWidget(this);
    tabs->setGeometry(0, 0, 700, 800);

    tabOps = new QWidget();
    tabs->addTab(tabOps, TAB_OPERATIONS);

    setupOperationsTab();
    updateOperations();
}

MainWindow::~MainWindow()
{
}

QString MainWindow::mainStyle() {
    return STYLE_MAIN;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(30, 30, 30));
    QMainWindow::paintEvent(event);
}

void MainWindow::setupOperationsTab() {
    QVBoxLayout *lay = new QVBoxLayout(tabOps);
    lay->setSpacing(12);
    lay->setContentsMargins(16, 16, 16, 16);

    groupSettings = new QGroupBox(TEXT_SETTINGS);
    QFormLayout *setLay = new QFormLayout(groupSettings);
    
    comboDataType = new QComboBox();
    comboDataType->addItems({TYPE_INT, TYPE_DOUBLE});
    comboContainer = new QComboBox();
    comboContainer->addItems({CONT_ARRAY, CONT_LIST, CONT_BIT});
    comboOperation = new QComboBox();
    
    setLay->addRow(TEXT_DATA_TYPE, comboDataType);
    setLay->addRow(TEXT_CONTAINER, comboContainer);
    setLay->addRow(TEXT_OPERATION, comboOperation);
    lay->addWidget(groupSettings);

    groupSeqA = new QGroupBox(TEXT_SEQ_A);
    QVBoxLayout *aLay = new QVBoxLayout(groupSeqA);
    lineSeqA = new QLineEdit();
    lineSeqA->setPlaceholderText("Пример: 1 2 3 4 5");
    aLay->addWidget(lineSeqA);
    lay->addWidget(groupSeqA);

    groupSeqB = new QGroupBox(TEXT_SEQ_B);
    QVBoxLayout *bLay = new QVBoxLayout(groupSeqB);
    lineSeqB = new QLineEdit();
    lineSeqB->setPlaceholderText("Пример: 6 7 8");
    bLay->addWidget(lineSeqB);
    lay->addWidget(groupSeqB);

    groupArgs = new QGroupBox(TEXT_ARGS);
    QFormLayout *argsLay = new QFormLayout(groupArgs);
    labelValue = new QLabel(TEXT_VALUE);
    lineValue = new QLineEdit();
    argsLay->addRow(labelValue, lineValue);

    labelIndex = new QLabel(TEXT_INDEX);
    lineIndex = new QLineEdit();
    argsLay->addRow(labelIndex, lineIndex);

    labelStart = new QLabel(TEXT_START);
    lineStart = new QLineEdit();
    argsLay->addRow(labelStart, lineStart);

    labelEnd = new QLabel(TEXT_END);
    lineEnd = new QLineEdit();
    argsLay->addRow(labelEnd, lineEnd);
    lay->addWidget(groupArgs);

    btnRun = new QPushButton(TEXT_RUN);
    lay->addWidget(btnRun);

    groupResult = new QGroupBox(TEXT_GROUP_RESULT);
    QVBoxLayout *resLay = new QVBoxLayout(groupResult);
    labelResultTitle = new QLabel(TEXT_RESULT_LBL);
    labelResultTitle->setStyleSheet(STYLE_LABEL_RESULT);
    
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(6);
    shadow->setColor(Qt::black);
    shadow->setOffset(1, 1);
    labelResultTitle->setGraphicsEffect(shadow);
    resLay->addWidget(labelResultTitle);
    
    textResult = new QTextEdit();
    textResult->setReadOnly(true);
    resLay->addWidget(textResult);
    lay->addWidget(groupResult);

    connect(comboContainer, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onContainerChanged);
    connect(comboOperation, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onOperationChanged);
    connect(btnRun, &QPushButton::clicked, this, &MainWindow::onRun);
}

void MainWindow::updateOperations() {
    comboOperation->blockSignals(true);
    comboOperation->clear();
    comboOperation->addItem("GetFirst()", 0);
    comboOperation->addItem("GetLast()", 1);
    comboOperation->addItem("Get(index)", 2);
    comboOperation->addItem("GetLength()", 3);
    comboOperation->addItem("GetSubsequence(start, end)", 4);
    comboOperation->addItem("Append(item)", 5);
    comboOperation->addItem("Prepend(item)", 6);
    comboOperation->addItem("InsertAt(item, index)", 7);
    comboOperation->addItem("Concat(list)", 8);

    if(comboContainer->currentText() == CONT_BIT) {
        comboOperation->addItem("AND (&)", 10);
        comboOperation->addItem("OR (|)", 11);
        comboOperation->addItem("XOR (^)", 12);
        comboOperation->addItem("NOT (~)", 13);
    } else {
        comboOperation->addItem("ReflectSum()", 9);
        comboOperation->addItem("Map (x * 2)", 14);
        comboOperation->addItem("Reduce (sum)", 15);
        comboOperation->addItem("Where (x > 60)", 16);
    }
    comboOperation->blockSignals(false);
    onOperationChanged();
}

void MainWindow::onContainerChanged() {
    if(comboContainer->currentText() == CONT_BIT) {
        comboDataType->setCurrentIndex(0);
        comboDataType->setEnabled(false);
    } else {
        comboDataType->setEnabled(true);
    }
    updateOperations();
}

void MainWindow::onOperationChanged() {
    int op = comboOperation->currentData().toInt();
    
    groupSeqB->setVisible(op == 8 || op == 10 || op == 11 || op == 12);
    
    bool showVal = (op == 5 || op == 6 || op == 7);
    lineValue->setVisible(showVal);
    labelValue->setVisible(showVal);

    bool showIdx = (op == 2 || op == 7);
    lineIndex->setVisible(showIdx);
    labelIndex->setVisible(showIdx);

    bool showBounds = (op == 4);
    lineStart->setVisible(showBounds);
    labelStart->setVisible(showBounds);
    lineEnd->setVisible(showBounds);
    labelEnd->setVisible(showBounds);

    groupArgs->setVisible(showVal || showIdx || showBounds);
    textResult->clear();
}

template <typename T>
T parseVal(const QString& str) {
    if constexpr (std::is_same_v<T, int>) return str.toInt();
    else return str.toDouble();
}

template <typename T, template <typename> class Container>
Container<T> createSeq(const QString& str) {
    if(str.trimmed().isEmpty()) return Container<T>();
    
    QStringList parts = str.split(QRegularExpression("[\\s,]+"), Qt::SkipEmptyParts);
    T* raw = new T[parts.size()];
    for(size_t i = 0; i < parts.size(); ++i) {
        raw[i] = parseVal<T>(parts[i]);
    }
    Container<T> seq(raw, parts.size());
    delete[] raw;
    return seq;
}

template <typename T>
BitSequence<T> createBitSeq(const QString& str) {
    if(str.trimmed().isEmpty()) return BitSequence<T>();
    
    QStringList parts = str.split(QRegularExpression("[\\s,]+"), Qt::SkipEmptyParts);
    Bit<T>* raw = new Bit<T>[parts.size()];
    for(size_t i = 0; i < parts.size(); ++i) {
        int parsed = parts[i].toInt();
        raw[i] = Bit<T>(parsed != 0 ? 1 : 0);
    }
    BitSequence<T> seq(raw, parts.size());
    delete[] raw;
    return seq;
}

template <typename T>
QString formatSeq(Sequence<T>* seq) {
    QStringList lst;
    for(size_t i = 0; i < seq->GetLength(); ++i) {
        if constexpr (std::is_same_v<T, double>) {
            lst << QString::number(seq->Get(i), 'f', 4);
        } else {
            lst << QString::number(seq->Get(i));
        }
    }
    return lst.join(" ");
}

template <typename T>
QString formatBitSeq(BitSequence<T>* seq) {
    QStringList lst;
    for(size_t i = 0; i < seq->GetLength(); ++i) {
        lst << QString::number(bool(seq->Get(i)));
    }
    return lst.join(" ");
}

template <typename T, template <typename> class Container>
void MainWindow::executeStandard() {
    Container<T> seqA = createSeq<T, Container>(lineSeqA->text());
    int op = comboOperation->currentData().toInt();
    QString res;
    bool mutates = false; 

    if(op == 0) res = QString::number(seqA.GetFirst());
    else if(op == 1) res = QString::number(seqA.GetLast());
    else if(op == 2) res = QString::number(seqA.Get(lineIndex->text().toULongLong()));
    else if(op == 3) res = QString::number(seqA.GetLength());
    else if(op == 4) {
        auto sub = seqA.GetSubsequence(lineStart->text().toULongLong(), lineEnd->text().toULongLong());
        res = formatSeq<T>(sub);
        delete sub;
    }
    else if(op == 5) {
        seqA.Append(parseVal<T>(lineValue->text()));
        res = formatSeq<T>(&seqA);
        mutates = true;
    }
    else if(op == 6) {
        seqA.Prepend(parseVal<T>(lineValue->text()));
        res = formatSeq<T>(&seqA);
        mutates = true;
    }
    else if(op == 7) {
        seqA.InsertAt(parseVal<T>(lineValue->text()), lineIndex->text().toULongLong());
        res = formatSeq<T>(&seqA);
        mutates = true;
    }
    else if(op == 8) {
        Container<T> seqB = createSeq<T, Container>(lineSeqB->text());
        seqA.Concat(&seqB);
        res = formatSeq<T>(&seqA);
        mutates = true;
    }
    else if(op == 9) {
        Sequence<T>* ref = seqA.ReflectSum();
        if(ref) {
            res = formatSeq<T>(ref);
            delete ref;
        } else {
            res = "Не поддерживается";
        }
    }
    else if(op == 14) {
        auto mapped = Map<T, T>(&seqA, double_val<T>);
        res = formatSeq<T>(mapped);
        delete mapped;
        mutates = true; 
    }
    else if(op == 15) {
        T reduced = Reduce<T, T>(&seqA, sum_func<T>, static_cast<T>(0));
        if constexpr (std::is_same_v<T, double>) {
            res = QString::number(reduced, 'f', 4);
        } else {
            res = QString::number(reduced);
        }
    }
    else if(op == 16) {
        auto filtered = Where<T>(&seqA, is_big<T>);
        res = formatSeq<T>(filtered);
        delete filtered;
        mutates = true;
    }
    
    textResult->setPlainText(res);
    
    if (mutates) {
        lineSeqA->setText(res);
    }
}

template <typename T>
void MainWindow::executeBit() {
    BitSequence<T> seqA = createBitSeq<T>(lineSeqA->text());
    int op = comboOperation->currentData().toInt();
    QString res;
    bool mutates = false;

    if(op == 0) res = QString::number(bool(seqA.GetFirst()));
    else if(op == 1) res = QString::number(bool(seqA.GetLast()));
    else if(op == 2) res = QString::number(bool(seqA.Get(lineIndex->text().toULongLong())));
    else if(op == 3) res = QString::number(seqA.GetLength());
    else if(op == 4) {
        auto sub = seqA.GetSubsequence(lineStart->text().toULongLong(), lineEnd->text().toULongLong());
        res = formatBitSeq<T>(sub);
        delete sub;
    }
    else if(op == 5) {
        int parsed = lineValue->text().toInt();
        seqA.Append(Bit<T>(parsed != 0 ? 1 : 0));
        res = formatBitSeq<T>(&seqA);
        mutates = true;
    }
    else if(op == 6) {
        int parsed = lineValue->text().toInt();
        seqA.Prepend(Bit<T>(parsed != 0 ? 1 : 0));
        res = formatBitSeq<T>(&seqA);
        mutates = true;
    }
    else if(op == 7) {
        int parsed = lineValue->text().toInt();
        seqA.InsertAt(Bit<T>(parsed != 0 ? 1 : 0), lineIndex->text().toULongLong());
        res = formatBitSeq<T>(&seqA);
        mutates = true;
    }
    else if(op == 8) {
        BitSequence<T> seqB = createBitSeq<T>(lineSeqB->text());
        seqA.Concat(&seqB);
        res = formatBitSeq<T>(&seqA);
        mutates = true;
    }
    else if(op == 10) {
        BitSequence<T> seqB = createBitSeq<T>(lineSeqB->text());
        BitSequence<T> out = seqA & seqB;
        res = formatBitSeq<T>(&out);
        mutates = true;
    }
    else if(op == 11) {
        BitSequence<T> seqB = createBitSeq<T>(lineSeqB->text());
        BitSequence<T> out = seqA | seqB;
        res = formatBitSeq<T>(&out);
        mutates = true;
    }
    else if(op == 12) {
        BitSequence<T> seqB = createBitSeq<T>(lineSeqB->text());
        BitSequence<T> out = seqA ^ seqB;
        res = formatBitSeq<T>(&out);
        mutates = true;
    }
    else if(op == 13) {
        BitSequence<T> out = ~seqA;
        res = formatBitSeq<T>(&out);
        mutates = true;
    }
    
    textResult->setPlainText(res);
    
    if (mutates) {
        lineSeqA->setText(res);
    }
}

void MainWindow::onRun() {
    try {
        int cont = comboContainer->currentIndex();
        int typeIdx = comboDataType->currentIndex();

        if (cont == 0) {
            if(typeIdx == 0) executeStandard<int, ArraySequence>();
            else executeStandard<double, ArraySequence>();
        } else if (cont == 1) {
            if(typeIdx == 0) executeStandard<int, ListSequence>();
            else executeStandard<double, ListSequence>();
        } else if (cont == 2) {
            executeBit<int>();
        }
    } catch (const Exception& e) {
        QMessageBox::warning(this, ERR_TITLE, QString::fromUtf8(e.what()));
    } catch (...) {
        QMessageBox::warning(this, ERR_TITLE, ERR_INVALID_INPUT);
    }
}