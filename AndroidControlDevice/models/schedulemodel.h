#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QAbstractListModel>

class ScheduleList;

class ScheduleModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ScheduleList *list READ list WRITE setList)

public:
    explicit ScheduleModel(QObject *parent = nullptr);

    enum {
//        DoneRole = Qt::UserRole,
//        DescriptionRole
//        int scheduleID;
        scheduleIDRole,
//        QString scheduleUUID;
        scheduleUUIDRole,
//        int userID;
        userIDRole,
//        QString userName;
        userNameRole,
//        int pinID;
        pinIDRole,
//        QString pinUUID;
        pinUUIDRole,
//        QString pinName;
        pinNameRole,
//        QString scheduleName;
        scheduleNameRole,
//        QString minute;
        minuteRole,
//        QString hour;
        hourRole,
//        QString dayOfMonth;
        dayOfMonthRole,
//        QString month;
        monthRole,
//        QString dayOfWeek;
        dayOfWeekRole,
//        QString timeZone;
        timeZoneRole,
//        QString value;
        valueRole,
//        QString description;
        descriptionRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ScheduleList *list() const;
    void setList(ScheduleList *list);

private:
    ScheduleList *mList;
};

#endif // SCHEDULEMODEL_H
