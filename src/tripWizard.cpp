#include "tripWizard.h"

#include <stdexcept>
#include <iostream>
#include <format>
#include <variant>

#include "trips/trip.h"
#include "filters/universalFilter.h"
#include "groupers/tripGroupers.h"

#include "printers/tripPrinter.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

size_t TripWizard::getConsoleWidth()
{    
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    #endif
}

void TripWizard::run(const Trips &trips)
{
    while(mWizardState != WizardState::Exit)
    {
        switch (mWizardState)
        {
            case WizardState::ConfiguringFilter:
                handleFilter();
                break;

            case WizardState::ConfiguringGrouping:
                handleGrouping();
                break;
            
            case WizardState::ConfiguringAggregation:
                handleAggregation();
                break;

            case WizardState::ConfiguringOutput:
                handleOutput();
                break;

            case WizardState::ConfiguringOutputStyle:
                handleOutputStyle();
                break;

            case WizardState::Finalizing:
                execute(trips);
                break;
            
            default:
                throw "This should not happen...";
                break;
        }
    }
}

void TripWizard::handleFilter()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "   SCHRITT 1: DATEN FILTERN" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Wie möchten Sie die Daten filtern?" << std::endl;
    std::cout << "1. Kein Filter" << std::endl;
    std::cout << "2. Nach Jahr filtern" << std::endl;
    std::cout << "3. Nach Verkehrsmittel filtern" << std::endl;
    
    size_t filterNum = getNumberFromCommandLine(1, 3);

    switch(filterNum)
    {
        case 1:
            // no filter, so nothing happens
            break;

        case 2:
            // select a certain year
            std::cout << "\nFür welches Jahr sollen Daten angezeigt werden?" << std::endl;
            mFilters.emplace_back(Filter::filterByYear(static_cast<int>(getNumberFromCommandLine(2000, 2100))));
            break;

        case 3:
            // select a transport type
            std::cout << "\nWelches Verkehrsmittel?" << std::endl;
            std::cout << "1. Fernverkehr\n2. Regionalverkehr\n3. S-Bahn\n4. U-Bahn\n5. Bus\n6. Tram\n7. Alle Züge" << std::endl;
            
            // Mapping der Eingabe auf deinen TransportType Enum
            size_t transportTypeNum = getNumberFromCommandLine(1, 7);

            switch(transportTypeNum)
            {
                case 1:
                    mFilters.emplace_back(Filter::filterByTransportType(TransportType::Fernverkehr));
                    break;
                case 2:
                    mFilters.emplace_back(Filter::filterByTransportType(TransportType::Regionalverkehr));
                    break;
                case 3:
                    mFilters.emplace_back(Filter::filterByTransportType(TransportType::SBahn));
                    break;
                case 4:
                    mFilters.emplace_back(Filter::filterByTransportType(TransportType::UBahn));
                    break;
                case 5:
                    mFilters.emplace_back(Filter::filterByTransportType(TransportType::Bus));
                    break;
                case 6:
                    mFilters.emplace_back(Filter::filterByTransportType(TransportType::Tram));
                    break;
                case 7:
                    mFilters.emplace_back(Filter::onlyTrainTrips());
                    break;
            }
            break;
    }

    // go to grouping after filtering
    mWizardState = WizardState::ConfiguringGrouping;
}

void TripWizard::handleGrouping()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "   SCHRITT 2: GRUPPIERUNG WÄHLEN" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Nach welchem Kriterium sollen die Fahrten zusammengefasst werden?" << std::endl;
    std::cout << "1. Keine Gruppierung" << std::endl;
    std::cout << "2. Nach Verkehrsmittel" << std::endl;
    std::cout << "3. Nach Start-Station" << std::endl;
    std::cout << "4. Nach Ziel-Station" << std::endl;
    std::cout << "5. Nach Monat" << std::endl;
    std::cout << "6. Nach betretenen Stationen" << std::endl;
    std::cout << "7. Nach allen angefahrenden Stationen" << std::endl;
    std::cout << "0. [ZURÜCK zum Filter]" << std::endl;

    size_t choice = getNumberFromCommandLine(0, 7);

    switch(choice)
    {
        case 0:
            mFilters.clear(); // clear all filters
            mWizardState = WizardState::ConfiguringFilter;
            break;

        case 1:
            mGroupingType = GroupingType::None;
            mWizardState = WizardState::ConfiguringAggregation;
            break;

        case 2:
            mGroupingType = GroupingType::ByTransportType;
            mWizardState = WizardState::ConfiguringAggregation;
            break;

        case 3:
            mGroupingType = GroupingType::ByOrigin;
            mWizardState = WizardState::ConfiguringAggregation;
            break;

        case 4:
            mGroupingType = GroupingType::ByDestination;
            mWizardState = WizardState::ConfiguringAggregation;
            break;

        case 5:
            mGroupingType = GroupingType::ByMonth;
            mWizardState = WizardState::ConfiguringAggregation;
            break;

        case 6:
            mGroupingType = GroupingType::ByVisitedStations;
            mWizardState = WizardState::ConfiguringAggregation;
            break;

        case 7:
            mGroupingType = GroupingType::ByPassedStops;
            mWizardState = WizardState::ConfiguringAggregation;
            break;
    }
}

void TripWizard::handleAggregation()
{
    bool noGrouping = mGroupingType == GroupingType::None;
    std::cout << "\n========================================" << std::endl;
    std::cout << "   SCHRITT 3: AGGREGATION WÄHLEN" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Welcher Wert soll berechnet werden?" << std::endl;
    std::cout << "1. Anzahl der Fahrten" << std::endl;
    std::cout << "2. Distanz" << std::endl;
    std::cout << "3. Dauer" << std::endl;
    std::cout << "4. Geschwindigkeit" << std::endl;
    if(noGrouping) std::cout << "5. Nicht aggregieren" << std::endl;
    std::cout << "0. [ZURÜCK zur Gruppierung]" << std::endl;

    size_t choice = getNumberFromCommandLine(0, 4 + (noGrouping ? 1 : 0));

    switch (choice)
    {
        case 0:
            mWizardState = WizardState::ConfiguringGrouping;
            break;

        case 1:
            mAggregationType = AggregationType::ByCount;
            mWizardState = WizardState::ConfiguringOutput;
            break;

        case 2:
            mAggregationType = AggregationType::ByDistance;
            mWizardState = WizardState::ConfiguringOutput;
            break;

        case 3:
            mAggregationType = AggregationType::ByDuration;
            mWizardState = WizardState::ConfiguringOutput;
            break;

        case 4:
            mAggregationType = AggregationType::BySpeed;
            mWizardState = WizardState::ConfiguringOutput;
            break;

        case 5:
            mAggregationType = AggregationType::None;
            mWizardState = WizardState::ConfiguringOutput;
            break;
    }
}

void TripWizard::handleOutput()
{
    // Averaging only makes sense if we aggregate by distance or duration
    bool averagePossible = (mAggregationType == AggregationType::ByDistance || mAggregationType == AggregationType::ByDuration);

    if (!averagePossible)
    {
        mOutputType = OutputType::AsTotalValues;
        mWizardState = WizardState::ConfiguringOutputStyle;
        return;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "   SCHRITT 4: AUSGABE-FORMAT" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Wie sollen die Werte dargestellt werden?" << std::endl;
    std::cout << "1. Als Summe" << std::endl;
    std::cout << "2. Als Durchschnitt" << std::endl;
    std::cout << "0. [ZURÜCK zur Aggregation]" << std::endl;

    size_t choice = getNumberFromCommandLine(0, 2);

    switch (choice)
    {
        case 0:
            mWizardState = WizardState::ConfiguringAggregation;
            break;

        case 1:
            mOutputType = OutputType::AsTotalValues;
            mWizardState = WizardState::ConfiguringOutputStyle;
            break;

        case 2:
            mOutputType = OutputType::AsAverages;
            mWizardState = WizardState::ConfiguringOutputStyle;
            break;
    }
}

void TripWizard::handleOutputStyle()
{
    bool mapPossible = mGroupingType == GroupingType::ByOrigin || mGroupingType == GroupingType::ByDestination || mGroupingType == GroupingType::ByVisitedStations || mGroupingType == GroupingType::ByPassedStops;
    if(!mapPossible)
    {
        mOutputStyle = OutputStyle::AsChart;
        mWizardState = WizardState::Finalizing;
        return;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "   SCHRITT 5: AUSGABE-STYLE" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Wie sollen die Werte dargestellt werden?" << std::endl;
    std::cout << "1. Als Diagramm" << std::endl;
    std::cout << "2. Als Karte" << std::endl;
    std::cout << "0. [ZURÜCK zur Ausgabe]" << std::endl;

    size_t choice = getNumberFromCommandLine(0, 2);

    switch (choice)
    {
        case 0:
            mWizardState = WizardState::ConfiguringOutput;
            break;

        case 1:
            mOutputStyle = OutputStyle::AsChart;
            mWizardState = WizardState::Finalizing;
            break;

        case 2:
            mOutputStyle = OutputStyle::AsMap;
            mWizardState = WizardState::Finalizing;
            break;
    }
}

void TripWizard::execute(const Trips &trips)
{
    Trips modifiableTrips = trips;

    for(const auto &filterFunction : mFilters)
    {
        UniversalFilter::filterTrips(modifiableTrips, filterFunction);
    }

    if(modifiableTrips.empty())
    {
        std::cout << "\n[!] Keine Trips entsprechen den gewählten Filtern." << std::endl;
        mWizardState = WizardState::ConfiguringFilter;
        return;
    }

    switch (mGroupingType)
    {
        case GroupingType::ByTransportType:
            processGrouping<TransportType>(modifiableTrips, TripGrouper::byTransportType());
            break;

        case GroupingType::ByOrigin:
            processGrouping<Station>(modifiableTrips, TripGrouper::byOrigin());
            break;

        case GroupingType::ByDestination:
            processGrouping<Station>(modifiableTrips, TripGrouper::byDestination());
            break;

        case GroupingType::ByMonth:
            processGrouping<std::string>(modifiableTrips, TripGrouper::byMonth());
            break;

        case GroupingType::ByVisitedStations:
            processGrouping<Station>(modifiableTrips, TripGrouper::byVisitedStations());
            break;

        case GroupingType::ByPassedStops:
            processGrouping<Station>(modifiableTrips, TripGrouper::byPassedStops());
            break;

        case GroupingType::None:
            if(mAggregationType == AggregationType::None)
            {
                std::cout << Printers::PrettyWrapper(modifiableTrips) << std::endl;
            }
            else
            {
                processGrouping<std::string>(modifiableTrips, TripGrouper::byNone());
            }
            break;
    }

    std::cout << "\nEnter für nächste Auswertung.";
    std::string dummy;
    std::getline(std::cin, dummy);
    
    mWizardState = WizardState::ConfiguringFilter;
    mFilters.clear();
}

size_t TripWizard::getNumberFromCommandLine(size_t min, size_t max)
{
    std::string input;

    while(true)
    {
        std::cout << " > ";
        std::getline(std::cin, input);
        try
        {
            size_t val = std::stoull(input);
            if(val >= min && val <= max)
            {
                return val;
            }
            else
            {
                throw std::out_of_range("");
            }
        }
        catch(...)
        {
            std::cout << std::format("Ungültige Eingabe \"{}\", bitte Bereich {}-{} beachten!", input, min, max);
        }
        
    }
}


