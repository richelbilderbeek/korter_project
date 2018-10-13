#ifndef KORTER_PROJECT_QT_MENU_DIALOG_H
#define KORTER_PROJECT_QT_MENU_DIALOG_H

#include <QDialog>

namespace Ui {
  class qt_menu_dialog;
}

namespace ribi {
namespace kp {

class qt_menu_dialog : public QDialog
{
  Q_OBJECT

public:
  explicit qt_menu_dialog(QWidget *parent = 0);
  qt_menu_dialog(const qt_menu_dialog&) = delete;
  qt_menu_dialog& operator=(const qt_menu_dialog&) = delete;
  ~qt_menu_dialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_about_clicked();
  void on_button_start_clicked();
  void on_button_quit_clicked();

private:
  Ui::qt_menu_dialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace mb
} //~namespace ribi

#endif // KORTER_PROJECT_QT_MENU_DIALOG_H
