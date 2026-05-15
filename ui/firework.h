#pragma once
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QColor>
#include <cmath>
#include <cstdlib>

struct Particle {
    QPointF pos;
    QPointF vel;
    QColor color;
    float life;
};

class FireworkWidget : public QWidget {
    Q_OBJECT
public:
    explicit FireworkWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
        setWindowFlags(Qt::FramelessWindowHint);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &FireworkWidget::update_particles);
    }

    void launch() {
        particles.clear();

        spawnBurst(width() * 0.3, height() * 0.3);
        spawnBurst(width() * 0.7, height() * 0.25);
        spawnBurst(width() * 0.5, height() * 0.4);
        timer->start(30);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        for (auto &pt : particles) {
            p.setOpacity(pt.life);
            p.setBrush(pt.color);
            p.setPen(Qt::NoPen);
            int r = 4 + (1.0 - pt.life) * 2;
            p.drawEllipse(pt.pos, r, r);
        }
    }

private slots:
    void update_particles() {
        for (auto &pt : particles) {
            pt.pos += pt.vel;
            pt.vel.ry() += 0.3; 
            pt.life -= 0.02f;
        }
        particles.erase(
            std::remove_if(particles.begin(), particles.end(),
                           [](const Particle &p){ return p.life <= 0; }),
            particles.end());

        if (particles.isEmpty()) timer->stop();
        update();
    }

private:
    QTimer *timer;
    QVector<Particle> particles;

    void spawnBurst(float cx, float cy) {
        QList<QColor> colors = {
            Qt::red, Qt::yellow, Qt::cyan, Qt::magenta,
            QColor(255,165,0), Qt::green, Qt::white
        };
        for (int i = 0; i < 80; i++) {
            float angle = (rand() % 360) * M_PI / 180.0f;
            float speed = 2.0f + (rand() % 40) / 10.0f;
            Particle pt;
            pt.pos = QPointF(cx, cy);
            pt.vel = QPointF(cos(angle)*speed, sin(angle)*speed);
            pt.color = colors[rand() % colors.size()];
            pt.life = 0.7f + (rand() % 30) / 100.0f;
            particles.append(pt);
        }
    }
};