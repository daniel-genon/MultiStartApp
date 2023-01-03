cmake_minimum_required(VERSION 3.5)

project(multistartapp VERSION 5.4.0 LANGUAGES CXX)


set(QT_VERSION_MAJOR 6)
# décommenter la ligne qui suit pour la version 5.15
#set(QT_VERSION_MAJOR 5)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
else()
    find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
endif()

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

message(STATUS "****** CMake a trouvé la version Qt : ${Qt${QT_VERSION_MAJOR}_VERSION} ******")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        bloc/ficbin.cpp
        bloc/ficbinbase.cpp
        bloc/ficbinbloc.cpp
        bloc/utilficbinbloc.cpp
        bloc/fictexte.cpp
        bloc/fblocconfig.cpp
        bloc/fbloccontexte.cpp
        bloc/fblocobjetcontexte.cpp
        bloc/fblocsessionmultiapp.cpp
        bloc/fblocprojetmapp.cpp
        bloc/ficbin.h
        bloc/ficbinbase.h
        bloc/ficbinbloc.h
        bloc/utilficbinbloc.h
        bloc/fictexte.h
        bloc/fblocconfig.h
        bloc/fbloccontexte.h
        bloc/fblocobjetcontexte.h
        bloc/fblocprojetmapp.h
        bloc/fblocsessionmultiapp.h
        dialogue/infovariablemsa.cpp
        dialogue/messagemsa.cpp
        dialogue/apropos.cpp
        dialogue/choisirfichiertravail.cpp
        dialogue/creeruncontexte.cpp
        dialogue/chargeruncontexte.cpp
        dialogue/creerunprojet.cpp
        dialogue/dialogconfiggenerale.cpp
        dialogue/choisirfichierconfiguration.cpp
        dialogue/infovariablemsa.h
        dialogue/messagemsa.h
        dialogue/apropos.h
        dialogue/choisirfichiertravail.h
        dialogue/creeruncontexte.h
        dialogue/chargeruncontexte.h
        dialogue/creerunprojet.h
        dialogue/dialogconfiggenerale.h
        dialogue/choisirfichierconfiguration.h
        enrg/enrgconfig.cpp
        enrg/enrgfichier.cpp
        enrg/enrggraph.cpp
        enrg/enrglogiciel.cpp
        enrg/enrgpolice.cpp
        enrg/enrgobjetctx.cpp
        enrg/enrdefobjet.cpp
        enrg/enrgconnexion.cpp
        enrg/enrgancre.cpp
        enrg/enrgligne.cpp
        enrg/enrgvariablemsa.cpp
        enrg/enrgconfig.h
        enrg/enrgfichier.h
        enrg/enrggraph.h
        enrg/enrglogiciel.h
        enrg/enrgpolice.h
        enrg/enrgligne.h
        enrg/enrgobjetctx.h
        enrg/enrdefobjet.h
        enrg/enrgconnexion.h
        enrg/enrgancre.h
        enrg/enrgvariablemsa.h
        connexion.cpp
        graphiquesurface.cpp
        ancrage.cpp
        vue.cpp
        gerersession.cpp
        element.cpp
        logiciel.cpp
        fichier.cpp
        fichiertravail.cpp
        fichierconfiguration.cpp
        configurationobjet.cpp
        graphobjetactif.cpp
        demarreobjet.cpp
        ancrage.h
        graphobjetactif.h
        vue.h
        gerersession.h
        structuredemarreur.h
        element.h
        logiciel.h
        fichier.h
        fichiertravail.h
        fichierconfiguration.h
        connexion.h
        graphiquesurface.h
        configurationobjet.h
        demarreobjet.h
        dialogue/apropos.ui
        dialogue/choisirfichiertravail.ui
        dialogue/boitecontexte.ui
        dialogue/creerunprojet.ui
        dialogue/dialogconfiggenerale.ui
        dialogue/choisirfichierconfiguration.ui
        dialogue/infovariablemsa.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(multistartapp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        images.qrc
    )
else()
    add_executable(multistartapp ${PROJECT_SOURCES} images.qrc )
endif()

target_link_libraries(multistartapp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
install(TARGETS multistartapp BUNDLE DESTINATION . LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable(multistartapp)
endif()




