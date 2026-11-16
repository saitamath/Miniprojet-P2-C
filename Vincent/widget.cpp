#include "widget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QTime>
#include <QTimer>
#include <QPlainTextEdit>

Widget::Widget(QWidget *p_parent) : QWidget(p_parent)
{
    m_labelCompteur = new QLabel("Compteur : 0");
    QPushButton *boutonAjouter = new QPushButton("Ajouter 1");

    QVBoxLayout *disposition = new QVBoxLayout(this);
    disposition->addWidget(m_labelCompteur);
    disposition->addWidget(boutonAjouter);

    m_labelTrame = new QLabel("Trame : aucune");

    m_journal = new QPlainTextEdit;
    m_journal->setReadOnly(true);

    QPushButton *boutonArret = new QPushButton("ARRET");

    disposition->addWidget(m_labelTrame);
    disposition->addWidget(m_journal);
    disposition->addWidget(boutonArret);

    // Timer du contrôleur simulé
    m_minuterieTrame = new QTimer(this);

    connect(m_minuterieTrame, &QTimer::timeout,
            this, &Widget::lireTrame);

    m_minuterieTrame->start(200);

    // Bouton ARRET
    connect(boutonArret, &QPushButton::clicked,
            this, &Widget::arreter);

    // Bouton Ajouter 1
    connect(boutonAjouter, &QPushButton::clicked,
            this, &Widget::incrementer);

    // Timer du compteur
    m_minuterie = new QTimer(this);

    connect(m_minuterie, &QTimer::timeout,
            this, &Widget::incrementer);

    m_minuterie->start(1000);
}

void Widget::incrementer()
{
    m_compteur = m_compteur + 1;

    m_labelCompteur->setText(
        "Compteur : " + QString::number(m_compteur));
}

void Widget::lireTrame()
{
    const int x = QRandomGenerator::global()->bounded(256);
    const int y = QRandomGenerator::global()->bounded(256);

    const QString trame =
        QString::number(x) + ":" + QString::number(y);

    m_labelTrame->setText("Trame : " + trame);

    m_journal->appendPlainText(
        QTime::currentTime().toString("HH:mm:ss.zzz  ")
        + trame);
}

void Widget::arreter()
{
    m_minuterie->stop();
    m_minuterieTrame->stop();

    m_journal->appendPlainText("ARRET demande");
}
