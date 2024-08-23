#include "desk.h"

void s21::View::deleteGame() {
  for (int i = 0; i < 7; i++) {
    delete labels[i];
  }
  delete again_box;
  delete stats_box;
  delete mainLayout;
}

s21::View::View(Controller *controller) : controller_(controller) {
  this->resize(10 * 20 * 2 - 19, 10 * 20 * 2 + 18);
  this->setWindowTitle("BRICK GAME !");
  set_labels();
  this->show();
  start_ = true;
  snake_ = false;
  tetris_ = false;
  again_ = false;
  go_ = false;
  pause_ = false;
  win_ = false;

  timerId_ = startTimer(1);
}

void s21::View::set_labels() {
  mainLayout = new QVBoxLayout(this);
  QGridLayout *layout = new QGridLayout;
  stats_box = new QGroupBox();
  stats_box->setFlat(true);
  stats_box->setStyleSheet("QGroupBox#theBox {border:0;}");
  mainLayout->addWidget(stats_box);
  for (int i = 1; i < 4; ++i) {
    labels[i] = new QLabel();
    labels[i]->hide();
  }
  layout->addWidget(labels[1], 2, 2, 5, 2, Qt::AlignTop);
  layout->addWidget(labels[2], 3, 2, 5, 2, Qt::AlignTop);
  layout->addWidget(labels[3], 4, 2, 5, 2, Qt::AlignTop);

  layout->setColumnStretch(1, 10);
  stats_box->setLayout(layout);
  stats_box->hide();

  QGridLayout *layout1 = new QGridLayout;
  again_box = new QGroupBox();
  again_box->setFlat(true);
  again_box->setStyleSheet("QGroupBox#theBox {border:0;}");
  mainLayout->addWidget(again_box);
  for (int i = 4; i < 7; ++i) {
    labels[i] = new QLabel();

    labels[i]->hide();
  }
  layout1->addWidget(labels[4], 1, 1, 5, 2);
  layout1->addWidget(labels[5], 2, 1, 5, 2);
  layout1->addWidget(labels[6], 3, 1, 5, 2);

  layout1->setColumnStretch(1, 10);
  again_box->setLayout(layout1);
  again_box->hide();
  labels[0] = new QLabel("BRICK GAME: SNAKE[1] TETRIS[2] QUIT[q]");
  mainLayout->addWidget(labels[0]);
  for (int i = 0; i < 7; i++) {
    labels[i]->show();
  }
}

void s21::View::drawRecs(QPainter *qp) {
  qp->drawRect(1, 1, 213, 413);
  qp->drawRect(220, 1, 140, 413);
  if (snake_) labels[1]->setText(tr("Level %1").arg(controller_->lvl()));
  if (tetris_) labels[1]->setText(tr("Level %1").arg(controller_->lvl_t()));
  labels[1]->show();

  if (snake_) labels[2]->setText(tr("Score %1").arg(controller_->score()));
  if (tetris_) labels[2]->setText(tr("Score %1").arg(controller_->score_t()));
  labels[2]->show();

  if (snake_) labels[3]->setText(tr("Record %1").arg(controller_->highScore()));
  if (tetris_)
    labels[3]->setText(tr("Record %1").arg(controller_->highScore_t()));
  labels[3]->show();
  qp->drawRect(260, 25, 90, 30);
  qp->drawRect(260, 75, 90, 30);
  qp->drawRect(260, 125, 90, 30);
  qp->drawRect(260, 175, 90, 90);
}

void s21::View::drawField(QPainter *qp) {
  int *map = nullptr;
  if (snake_) map = controller_->map();
  if (tetris_) map = controller_->map_t();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      bool apple = false;
      if (map[10 * i + j] == 3) qp->setBrush(Qt::darkYellow);
      if (map[10 * i + j] == 1) qp->setBrush(Qt::darkGreen);
      if (map[10 * i + j] == 2) {
        qp->setBrush(Qt::darkRed);
        if (snake_) apple = true;
      }
      if (map[10 * i + j] == 4) qp->setBrush(Qt::darkMagenta);
      if (map[10 * i + j] == 5) qp->setBrush(QColorConstants::Svg::darkorange);
      if (map[10 * i + j] == 6) qp->setBrush(Qt::darkBlue);
      if (map[10 * i + j] == 7) qp->setBrush(Qt::darkCyan);
      if (!apple && map[10 * i + j] != 0)
        qp->drawRect(j * 20 + 10, i * 20 + 10, 20, 20);
      if (apple && map[10 * i + j] != 0)
        qp->drawEllipse(j * 20 + 10, i * 20 + 10, 20, 20);
    }
  }
}

void s21::View::drawNext(QPainter *qp) {
  int type = controller_->nextTetrType();
  int orint = controller_->nextTetrOrint();
  for (int i = 0; i < 4; i++) {
    if (type + 1 == 3) qp->setBrush(Qt::darkYellow);
    if (type + 1 == 1) qp->setBrush(Qt::darkGreen);
    if (type + 1 == 2) qp->setBrush(Qt::darkRed);
    if (type + 1 == 4) qp->setBrush(Qt::darkMagenta);
    if (type + 1 == 5) qp->setBrush(QColorConstants::Svg::darkorange);
    if (type + 1 == 6) qp->setBrush(Qt::darkBlue);
    if (type + 1 == 7) qp->setBrush(Qt::darkCyan);
    qp->drawRect(controller_->nextTetrCol(type, orint, i) * 20 + 270,
                 controller_->nextTetrRow(type, orint, i) * 20 + 185, 20, 20);
  }
}

void s21::View::action(int action) {
  switch (action) {
    case Qt::Key_Left:
      controller_->left();
      break;
    case Qt::Key_Right:
      controller_->right();
      break;
    case Qt::Key_Up:
      controller_->up();
      break;
    case Qt::Key_Down:
      controller_->down();
      break;
    case 'q':
    case 'Q':
      if (!pause_) {
        go_ = false;
        again_ = true;
      }
      break;
    case 'p':
    case 'P':
      if (!again_) {
        pause_ = go_;
        go_ = !pause_;
      }
      break;
    default:
      controller_->non();
      break;
  }
}

void s21::View::action_t(int action) {
  switch (action) {
    case Qt::Key_Left:
      controller_->left_t();
      break;
    case Qt::Key_Right:
      controller_->right_t();
      break;
    case Qt::Key_Up:
      controller_->up_t();
      break;
    case Qt::Key_Down:
      controller_->down_t();
      break;
    case ' ':
      controller_->drop_t();
      break;
    case 'q':
    case 'Q':
      if (!pause_) {
        go_ = false;
        again_ = true;
      }
      break;
    case 'p':
    case 'P':
      if (!again_) {
        pause_ = go_;
        go_ = !pause_;
      }
      break;
    default:
      break;
  }
}

void s21::View::actionMenu(int key) {
  switch (key) {
    case '1':
      controller_->again(true);
      snake_ = true;
      start_ = false;
      go_ = true;
      break;
    case '2':
      controller_->again_t(true);
      tetris_ = true;
      start_ = false;
      go_ = true;
      break;
    case 'q':
    case 'Q':
      exit(EXIT_SUCCESS);
      break;
    default:
      break;
  }
}

void s21::View::actionAgain(int key) {
  switch (key) {
    case 'y':
    case 'Y':
      if (snake_) controller_->again(true);
      if (tetris_) controller_->again_t(true);
      again_ = false;
      win_ = false;
      go_ = true;
      break;
    case 'n':
    case 'N':
      if (snake_) snake_ = false;
      if (tetris_) tetris_ = false;
      again_ = false;
      win_ = false;
      go_ = false;
      start_ = true;
      break;
    default:
      break;
  }
}

void s21::View::menu() {
  labels[1]->hide();
  labels[2]->hide();
  labels[3]->hide();
  stats_box->hide();
  labels[4]->hide();
  labels[5]->hide();
  labels[6]->hide();
  again_box->hide();
  labels[0]->show();

  update();
}

void s21::View::keyPressEvent(QKeyEvent *e) {
  int key = e->key();
  if (start_) actionMenu(key);
  if (snake_) action(key);
  if (again_ || win_) actionAgain(key);
  if (tetris_) action_t(key);
}

void s21::View::snake(QPainter *qp) {
  if (go_) {
    drawRecs(qp);
    qp->setBrush(Qt::darkMagenta);
    drawField(qp);

    if (controller_->win()) {
      go_ = false;
      win_ = true;
    }

    if (controller_->fail()) {
      go_ = false;
      again_ = true;
    }
  }
}

void s21::View::tetris(QPainter *qp) {
  if (go_) {
    drawRecs(qp);
    qp->setBrush(Qt::darkMagenta);
    drawField(qp);
    drawNext(qp);

    if (controller_->fail_t()) {
      go_ = false;
      again_ = true;
    }
  }
}

void s21::View::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter qp(this);
  if (snake_) snake(&qp);
  if (tetris_) tetris(&qp);
}

void s21::View::again() {
  labels[1]->hide();
  labels[2]->hide();
  labels[3]->hide();
  stats_box->hide();

  labels[4]->setText("The game is over.");
  labels[4]->show();

  labels[5]->setText(tr("You have %1 points.").arg(controller_->score()));
  labels[5]->show();

  labels[6]->setText("Want to start over?[y/n]");
  labels[6]->show();
  again_box->show();

  update();
}

void s21::View::pause() {
  labels[1]->hide();
  labels[2]->hide();
  labels[3]->hide();
  stats_box->hide();

  labels[4]->setText("PAUSE");
  labels[4]->show();
  labels[5]->hide();
  labels[6]->hide();
  again_box->show();

  update();
}

void s21::View::timerEvent(QTimerEvent *e) {
  Q_UNUSED(e);
  if (go_) {
    update();
    if (!labels[0]->isHidden()) {
      labels[0]->hide();
    }
    if (!labels[4]->isHidden()) {
      labels[4]->hide();
      labels[5]->hide();
      labels[6]->hide();
      again_box->hide();
    }
    if (stats_box->isHidden()) {
      labels[1]->show();
      labels[2]->show();
      labels[3]->show();
      stats_box->show();
    }
    timer();
    if (snake_) controller_->tick();
    if (tetris_) controller_->tick_t();

    update();
  }

  if (again_) {
    update();
    again();
  }

  if (pause_) {
    update();
    pause();
  }

  if (win_) {
    update();
    win();
  }

  if (start_) {
    update();
    menu();
  }
}

void s21::View::win() {
  labels[1]->hide();
  labels[2]->hide();
  labels[3]->hide();
  stats_box->hide();

  labels[4]->setText("You win!");
  labels[4]->show();

  labels[5]->setText(tr("You have %1 points.").arg(controller_->score()));
  labels[5]->show();

  labels[6]->setText("Want to start over?[y/n]");
  labels[6]->show();
  again_box->show();

  update();
}

void s21::View::timer() {
  if (snake_)
    std::this_thread::sleep_for(
        std::chrono::milliseconds(controller_->speed()));
  if (tetris_) std::this_thread::sleep_for(std::chrono::milliseconds(15));
}