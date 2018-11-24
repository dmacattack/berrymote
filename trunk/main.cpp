#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QDebug>
#include "berrymotemain.hpp"
#include <stdio.h>

// console colors
#define TXT_RED     "\x1b[31m"
#define TXT_GREEN   "\x1b[32m"
#define TXT_YELLOW  "\x1b[33m"
#define TXT_BLUE    "\x1b[34m"
#define TXT_MAGENTA "\x1b[35m"
#define TXT_CYAN    "\x1b[36m"
#define TXT_RESET   "\x1b[0m"

/*!
 * \brief trimFunctionName
 * remove the function params & brackets from the function name. i.e. (int argc, char **argv)
 * \param fn
 * \return
 */
QString trimFunctionName(const char* fn)
{
    QString noArgs = QString(fn).remove(QRegExp("\\((.*)\\)"));

    int spaceIdx = noArgs.indexOf(QChar(' '));
    int colonIdx = noArgs.indexOf("::");
    QString noType = noArgs;

    if (spaceIdx < colonIdx)
    {
        noType = noArgs.right(noArgs.length() - (spaceIdx+1) );
    }

    return noType;
}

/*!
 * \brief debugFormatting
 * Custom debug formatting with colors
 * \param type
 * \param context
 * \param msg
 */
void debugFormatting(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QString fn = trimFunctionName(context.function);

    switch (type)
    {
    case QtInfoMsg:
    case QtDebugMsg:
        fprintf(stderr, "%s[M] %s - %s%s\n", TXT_GREEN, fn.toStdString().c_str(), localMsg.constData(), TXT_RESET);
        break;
    case QtWarningMsg:
        fprintf(stderr, "%s[W] %s - %s%s\n", TXT_BLUE, context.function, localMsg.constData(), TXT_RESET);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "%s[C] %s - %s%s\n", TXT_RED, context.function, localMsg.constData(), TXT_RESET);
        break;
    case QtFatalMsg:
        fprintf(stderr, "%s[F] %s - %s%s\n", TXT_RED, context.function, localMsg.constData(), TXT_RESET);
        abort();
    }
}

/*!
 * \brief main
 * main function to init everything
 */
int main(int argc, char *argv[])
{
    qInstallMessageHandler(debugFormatting);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    QObject *pRootObj = engine.rootObjects().first();

    if (pRootObj == nullptr)
    {
        qCritical() << "root object is null";
    }
    else
    {
        BerrymoteMain *pMain = new BerrymoteMain(pRootObj);
        pMain->init();
    }

    return app.exec();
}
