/*
* This file is part of Converseen, an open-source batch image converter
* and resizer.
*
* (C) Francesco Mondello 2009-2013
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Contact e-mail: Faster <faster3ck@gmail.com>
*
*/

#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QMainWindow>
#include <QtGui>
#include <QFileInfo>
#include <QList>
#include <QSettings>
#include <QDropEvent>
#include "ui_mainwindow.h"
#include "converter.h"
#include "dialogquality.h"
#include "dialogconversionstatus.h"
#include "pixtreewidget.h"
#include "mylabelpreviewer.h"

class QDropEvent;

class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
    ~MainWindowImpl();
    void importListFromArgv(QString fileName);

private:
    void createActions();
    void setupMenu();
    void createContextMenu();
    void setFileInList(QString fileName);
    bool checkDuplicates(QStringList fileNames, int e);
    void convert();
    void fillTreeView();
    void loadFormats();
    void loadOptions();
    void loadQuality();

    void deleteItems(int selectedItems);

    void loadPreview(QString fileName);
    void showImageInformations();   // quello che succede alla selezione dell'item.

    void resetDisplays();

    QString destinationPath();

    QList<ImageAttributes> *iAList;

    Converter *convertThread;
    DialogConversionStatus *dlgCStatus;
    int curr_index;             // Indice dell'immagine che si sta processando dalla lista iAList

    int jpgQuality;             // Imposta la qualità jpg anche nel file ini
    int pngQuality;             // Imposta la qualità png anche nel file ini
    int img_width,img_height;  /* vengono riempiti solo quando un'immagine è selezionata.
                                  Riempire con dati su ImageAttributes potrebbe essere lento e non conveniente! */
    int new_img_width,new_img_height; /* Vengono riempiti con numeri che rappresentano i pixel dato che non capisco come
                                         si passa la corretta percentuale in virgola mobile a geometry*/
    double m_xResolution, m_yResolution;

    bool abort_all;

    QString m_bgColor;
private slots:
    void loadFiles(QStringList fileNames);
    void openFiles();
    void addFiles();
    void elabora();
    void setCurrentDirectory();
    void openOutDirectory();
    void removeItems();
    void removeAllItems();
    void setQuality();
    void selectGeometryUnit(QString unit);
    void relativeSizeW();
    void relativeSizeH();

    void onItemSelection();
    void editSettings();

    void about();

    void enableRenameLine();
    void enableShowPreview();

    void showNewSizePreview();

    void onPushResetClick();

    void startConversion();
    void nextConversion(int conv_status);

    void overwriteDialog(QString baseName);

    void stopProcess();
    void errorMessage(QString err_status);

    void choseBackgroundColor();

    void openPaypalLink();
};
#endif // MAINWINDOWIMPL_H