#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QPushButton>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    void setButtonsColorMapping();
    void setPressedButtonsColor();
    void setResult();
    void setButtonsMapping();
    void resetResult();
    Ui::Notepad *ui;
    bool resultLock = false;
    std::unordered_map<QPushButton*, QString> colorsLut;
};
#endif // NOTEPAD_H
