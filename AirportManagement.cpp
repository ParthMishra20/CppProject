#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QMap>
#include <QDateTime>

class AirportManagementSystem : public QWidget {
    Q_OBJECT

public:
    AirportManagementSystem(QWidget *parent = nullptr) : QWidget(parent) {
        initializeUI();
        connectSlots();
        initializeFlights();
        updateFlightList();
    }

private slots:
    void bookFlight() {
        QString passengerName = nameLineEdit->text();
        QString destination = destinationLineEdit->text();

        if (!passengerName.isEmpty() && !destination.isEmpty()) {
            QString flightNumber = generateRandomFlightNumber();
            QDateTime departureTime = QDateTime::currentDateTime().addSecs(3600 + (qrand() % 3600 * 24)); // Departure time is 1-24 hours from now
            bookedFlights[flightNumber] = {passengerName, destination, departureTime};
            updateFlightList();
            QMessageBox::information(this, "Booking Confirmation", "Flight booked for " + passengerName + " to " +
                                     destination + "\nYour Flight Number is: " + flightNumber +
                                     "\nDeparture Time: " + departureTime.toString("hh:mm AP"));
        } else {
            QMessageBox::warning(this, "Booking Error", "Please enter passenger name and destination.");
        }
    }

    void checkFlightStatus() {
        QListWidgetItem *selectedItem = flightListWidget->currentItem();
        if (selectedItem) {
            QString flightNumber = selectedItem->text();
            if (bookedFlights.contains(flightNumber)) {
                QPair<QString, QString> flightInfo = bookedFlights[flightNumber];
                QDateTime departureTime = bookedFlights[flightNumber].third;
                QMessageBox::information(this, "Flight Status", "Flight " + flightNumber + " to " + flightInfo.second +
                                         " is on time\nDeparture Time: " + departureTime.toString("hh:mm AP"));
            } else {
                QMessageBox::warning(this, "Flight Status", "Invalid flight number.");
            }
        } else {
            QMessageBox::warning(this, "Flight Status", "Please select a flight.");
        }
    }

    void cancelFlight() {
        QListWidgetItem *selectedItem = flightListWidget->currentItem();
        if (selectedItem) {
            QString flightNumber = selectedItem->text();
            if (bookedFlights.contains(flightNumber)) {
                QPair<QString, QString> flightInfo = bookedFlights[flightNumber];
                bookedFlights.remove(flightNumber);
                updateFlightList();
                QMessageBox::information(this, "Flight Cancellation", "Flight " + flightNumber + " to " + flightInfo.second +
                                         " has been canceled");
            } else {
                QMessageBox::warning(this, "Flight Cancellation", "Invalid flight number.");
            }
        } else {
            QMessageBox::warning(this, "Flight Cancellation", "Please select a flight.");
        }
    }

    void updateFlightList() {
        flightListWidget->clear();
        for (const QString &flightNumber : bookedFlights.keys()) {
            flightListWidget->addItem(flightNumber);
        }
    }

private:
    void initializeUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QLabel *titleLabel = new QLabel("Airport Management System", this);
        mainLayout->addWidget(titleLabel);

        QLabel *bookingLabel = new QLabel("Book a Flight", this);
        mainLayout->addWidget(bookingLabel);

        nameLabel = new QLabel("Passenger Name:", this);
        nameLineEdit = new QLineEdit(this);
        mainLayout->addWidget(nameLabel);
        mainLayout->addWidget(nameLineEdit);

        destinationLabel = new QLabel("Destination:", this);
        destinationLineEdit = new QLineEdit(this);
        mainLayout->addWidget(destinationLabel);
        mainLayout->addWidget(destinationLineEdit);

        bookButton = new QPushButton("Book", this);
        mainLayout->addWidget(bookButton);

        QLabel *statusLabel = new QLabel("Check Flight Status", this);
        mainLayout->addWidget(statusLabel);

        flightListWidget = new QListWidget(this);
        mainLayout->addWidget(flightListWidget);

        checkStatusButton = new QPushButton("Check Status", this);
        mainLayout->addWidget(checkStatusButton);

        QLabel *cancelLabel = new QLabel("Cancel a Flight", this);
        mainLayout->addWidget(cancelLabel);

        cancelFlightButton = new QPushButton("Cancel Flight", this);
        mainLayout->addWidget(cancelFlightButton);
    }

    void connectSlots() {
        connect(bookButton, &QPushButton::clicked, this, &AirportManagementSystem::bookFlight);
        connect(checkStatusButton, &QPushButton::clicked, this, &AirportManagementSystem::checkFlightStatus);
        connect(cancelFlightButton, &QPushButton::clicked, this, &AirportManagementSystem::cancelFlight);
    }

    void initializeFlights() {
        // Pre-populate bookedFlights for testing
        bookedFlights = {
            {"ABC123", {"John Doe", "New York", QDateTime::currentDateTime().addSecs(3600)}},
            {"DEF456", {"Jane Smith", "Los Angeles", QDateTime::currentDateTime().addSecs(7200)}},
            {"GHI789", {"Bob Johnson", "Chicago", QDateTime::currentDateTime().addSecs(10800)}},
        };
    }

    QString generateRandomFlightNumber() {
        return "XYZ" + QString::number(qrand() % 1000);
    }

    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *destinationLabel;
    QLineEdit *destinationLineEdit;
    QPushButton *bookButton;

    QListWidget *flightListWidget;
    QPushButton *checkStatusButton;

    QPushButton *cancelFlightButton;

    QMap<QString, QPair<QString, QString, QDateTime>> bookedFlights;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AirportManagementSystem airportSystem;
    airportSystem.show();

    return app.exec();
}

#include "main.moc"
