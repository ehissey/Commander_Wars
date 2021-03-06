#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include <QQmlEngine>

/**
 * @brief The Interpreter class java-script interpreter with easy access functions
 */
class Interpreter : public QQmlEngine
{
    Q_OBJECT

public:
    explicit Interpreter(QString script);
    explicit Interpreter();
    virtual ~Interpreter();

    static void setCppOwnerShip(QObject* object);
signals:

public slots:
    void openScript(QString script);
    void loadScript(QString content, QString script);
    QJSValue doFunction(QString func, QJSValueList& args);
    QJSValue doFunction(QString obj, QString func, const QJSValueList& args = QJSValueList());
    void cleanMemory();
    /**
     * @brief doString immediatly interprates the string with the javascript-interpreter
     * @param task string parsed to the interpreter
     */
    QJSValue doString(QString task);
    /**
     * @brief pushInt
     * @param value
     */
    void pushInt(QString name, qint32 value);
    void pushDouble(QString name, double value);
    void pushString(QString name, QString value);
    void pushObject(QString name, QObject* object);
    QJSValue newQObject(QObject* object);
    void deleteObject(QString name);

    qint32 getGlobalInt(QString var);
    bool getGlobalBool(QString var);
    double getGlobalDouble(QString var);
    QString getGlobalString(QString var);
    QJSValue getGlobal(QString var);
    void setGlobal(QString var, QJSValue obj);


private:
    void init();

};

#endif // INTERPRETER_H
