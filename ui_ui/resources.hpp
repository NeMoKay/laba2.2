#pragma once
#include <QString>

const QString APP_TITLE = "Менеджер последовательностей";
const QString TAB_OPERATIONS = "Операции";

const QString TEXT_SETTINGS = "Настройки операции";
const QString TEXT_DATA_TYPE = "Тип данных:";
const QString TEXT_CONTAINER = "Контейнер:";
const QString TEXT_OPERATION = "Операция:";

const QString TYPE_INT = "int";
const QString TYPE_DOUBLE = "double";

const QString CONT_ARRAY = "ArraySequence";
const QString CONT_LIST = "ListSequence";
const QString CONT_BIT = "BitSequence";

const QString TEXT_SEQ_A = "Последовательность A";
const QString TEXT_SEQ_B = "Последовательность B";
const QString TEXT_ARGS = "Аргументы";
const QString TEXT_VALUE = "Значение:";
const QString TEXT_INDEX = "Индекс:";
const QString TEXT_START = "Начало (индекс):";
const QString TEXT_END = "Конец (индекс):";

const QString TEXT_RUN = "Выполнить";
const QString TEXT_GROUP_RESULT = "Результат";
const QString TEXT_RESULT_LBL = "Итог:";

const QString ERR_TITLE = "Ошибка";
const QString ERR_INVALID_INPUT = "Некорректный ввод данных.";

const QString STYLE_LABEL_RESULT = "color: #a0c4ff; font-size: 13px; padding: 2px;";

const QString STYLE_MAIN = R"(
    QTabWidget::pane { border: 1px solid rgba(255,255,255,60); background: transparent; }
    QTabBar::tab { background: rgba(0,0,0,120); color: white; padding: 8px 20px; border: 1px solid rgba(255,255,255,60); border-radius: 4px 4px 0 0; }
    QTabBar::tab:selected { background: rgba(83,52,131,180); }
    QGroupBox { color: white; font-weight: bold; border: 1px solid rgba(255,255,255,70); border-radius: 8px; margin-top: 10px; padding-top: 10px; background: rgba(0,0,0,80); }
    QGroupBox::title { subcontrol-origin: margin; left: 12px; color: white; }
    QLabel { color: white; }
    QComboBox { background: rgba(0,0,0,200); color: white; border: 1px solid rgba(255,255,255,80); border-radius: 5px; padding: 5px; }
    QComboBox QAbstractItemView { background: rgba(20,20,20,240); color: white; selection-background-color: rgba(83,52,131,200); }
    QLineEdit { background: rgba(0,0,0,140); color: white; border: 1px solid rgba(255,255,255,80); border-radius: 5px; padding: 5px; }
    QTextEdit { background: rgba(0,0,0,120); color: #a0c4ff; border: 1px solid rgba(255,255,255,60); border-radius: 5px; font-size: 14px;}
    QPushButton { background: rgba(60,60,60,180); color: white; border: 1px solid rgba(255,255,255,100); border-radius: 6px; padding: 8px 16px; font-size: 13px; }
    QPushButton:hover { background: rgba(100,100,100,200); }
    QPushButton:pressed { background: rgba(40,40,40,200); }
    QPushButton:disabled { background: rgba(40,40,40,120); color: rgba(255,255,255,60); }
)";