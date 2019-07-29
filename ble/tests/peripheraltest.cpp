#include <QCoreApplication>
#include <QDebug>

#include <BluezQt/Adapter>
#include <BluezQt/GattApplication>
#include <BluezQt/GattCharacteristic>
#include <BluezQt/GattManager>
#include <BluezQt/GattService>
#include <BluezQt/InitManagerJob>
#include <BluezQt/LEAdvertisement>
#include <BluezQt/LEAdvertisingManager>
#include <BluezQt/Manager>

#include <ble/Converter.h>

using namespace BluezQt;
using namespace std::placeholders;

class Controller : public QObject
{
public:
    explicit Controller(QObject *parent = nullptr)
    {
        // Init BluezQt
        m_manager = new Manager(this);
        InitManagerJob *initJob = m_manager->init();
        initJob->exec();
        if (initJob->error()) {
            qWarning() << "Error initializing bluetooth manager:" << initJob->errorText();
            return;
        }

        m_advertisement = new LEAdvertisement({QStringLiteral("ad100000-d901-11e8-9f8b-f2801f1b9fd1")}, this);
        m_manager->usableAdapter()->leAdvertisingManager()->registerAdvertisement(m_advertisement);

        m_application = new GattApplication(this);
        auto service = new GattService(QStringLiteral("ad100000-d901-11e8-9f8b-f2801f1b9fd1"), true, m_application);

        auto peqCharc = new GattCharacteristic(QStringLiteral("ad10e100-d901-11e8-9f8b-f2801f1b9fd1"), service);
        peqCharc->setReadCallback(std::bind(&Controller::onReadFilters, this, common::FilterGroup::Peq));
        connect(peqCharc, &GattCharacteristic::valueWritten, std::bind(&Controller::onWriteFilters, this, common::FilterGroup::Peq, _1));
        m_charcs[common::FilterGroup::Peq] = peqCharc;

        auto auxCharc = new GattCharacteristic(QStringLiteral("ad10a100-d901-11e8-9f8b-f2801f1b9fd1"), service);
        auxCharc->setReadCallback(std::bind(&Controller::onReadFilters, this, common::FilterGroup::Aux));
        connect(auxCharc, &GattCharacteristic::valueWritten, std::bind(&Controller::onWriteFilters, this, common::FilterGroup::Aux, _1));
        m_charcs[common::FilterGroup::Aux] = auxCharc;

        m_manager->usableAdapter()->gattManager()->registerApplication(m_application);
    }
    ~Controller()
    {
        m_manager->usableAdapter()->leAdvertisingManager()->unregisterAdvertisement(m_advertisement);
        m_manager->usableAdapter()->gattManager()->unregisterApplication(m_application);
    }

private:
    QByteArray onReadFilters(common::FilterGroup group)
    {
        switch (group) {
        case common::FilterGroup::Aux:
            return m_converter.filtersToBle({{common::FilterType::Crossover, 3000.0}});
        case common::FilterGroup::Peq:
            return m_converter.filtersToBle( { { common::FilterType::Peak, 2335.0, -3.7, 0.7 },
                                               { common::FilterType::LowPass, 12222.0, 1.4, 0.5 },
                                               { common::FilterType::HighPass, 47.0, -3.3, 0.8 } });
        case common::FilterGroup::Invalid:
            return QByteArray();
        }
        return QByteArray();
    }

    void onWriteFilters(common::FilterGroup group, const QByteArray& value)
    {
        auto filters = m_converter.filtersFromBle(value);
        for (const auto& filter : filters) {
            qDebug() << "t:" << static_cast<uint>(filter.type)
                     << "f:" << filter.f
                     << "g:" << filter.g
                     << "q:" << filter.q;
        }
        qDebug() << "";
    }

    BluezQt::Manager* m_manager = nullptr;
    std::map<common::FilterGroup, BluezQt::GattCharacteristic*> m_charcs;
    BluezQt::GattApplication* m_application = nullptr;
    BluezQt::LEAdvertisement* m_advertisement = nullptr;
    ble::Converter m_converter;
};


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    new Controller();

    return app.exec();
}
