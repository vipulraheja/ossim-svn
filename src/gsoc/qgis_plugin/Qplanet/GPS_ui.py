# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/Users/Shared/Development/gsoc/OssimPlanetSasha/gui/GPS_ui.ui'
#
# Created: Wed Jun 24 11:38:14 2009
#      by: PyQt4 UI code generator 4.5
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(447, 430)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icons/icons/satellite.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        Form.setWindowIcon(icon)
        self.verticalLayout = QtGui.QVBoxLayout(Form)
        self.verticalLayout.setObjectName("verticalLayout")
        self.tabWidget_2 = QtGui.QTabWidget(Form)
        #self.tabWidget_2.setDocumentMode(False)
        self.tabWidget_2.setTabsClosable(False)
        self.tabWidget_2.setMovable(False)
        self.tabWidget_2.setObjectName("tabWidget_2")
        self.tab_5 = QtGui.QWidget()
        self.tab_5.setObjectName("tab_5")
        self.verticalLayout_7 = QtGui.QVBoxLayout(self.tab_5)
        self.verticalLayout_7.setObjectName("verticalLayout_7")
        self.Satellite = QtGui.QTextBrowser(self.tab_5)
        self.Satellite.setObjectName("Satellite")
        self.verticalLayout_7.addWidget(self.Satellite)
        self.tabWidget_2.addTab(self.tab_5, "")
        self.tab_6 = QtGui.QWidget()
        self.tab_6.setObjectName("tab_6")
        self.verticalLayout_3 = QtGui.QVBoxLayout(self.tab_6)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.WebMap = QtWebKit.QWebView(self.tab_6)
        self.WebMap.setUrl(QtCore.QUrl("about:blank"))
        self.WebMap.setObjectName("WebMap")
        self.verticalLayout_3.addWidget(self.WebMap)
        self.tabWidget_2.addTab(self.tab_6, "")
        self.verticalLayout.addWidget(self.tabWidget_2)
        self.GpsGroupBox = QtGui.QGroupBox(Form)
        self.GpsGroupBox.setObjectName("GpsGroupBox")
        self.verticalLayout_20 = QtGui.QVBoxLayout(self.GpsGroupBox)
        self.verticalLayout_20.setObjectName("verticalLayout_20")
        self.GpsGridLayout = QtGui.QGridLayout()
        self.GpsGridLayout.setObjectName("GpsGridLayout")
        self.Latlabel = QtGui.QLabel(self.GpsGroupBox)
        self.Latlabel.setObjectName("Latlabel")
        self.GpsGridLayout.addWidget(self.Latlabel, 0, 0, 1, 1)
        self.GPSlat = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSlat.setEchoMode(QtGui.QLineEdit.Normal)
        self.GPSlat.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSlat.setReadOnly(True)
        self.GPSlat.setObjectName("GPSlat")
        self.GpsGridLayout.addWidget(self.GPSlat, 0, 2, 1, 1)
        self.GPSEpt = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSEpt.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSEpt.setReadOnly(True)
        self.GPSEpt.setObjectName("GPSEpt")
        self.GpsGridLayout.addWidget(self.GPSEpt, 7, 2, 1, 1)
        self.Eptlabel = QtGui.QLabel(self.GpsGroupBox)
        self.Eptlabel.setObjectName("Eptlabel")
        self.GpsGridLayout.addWidget(self.Eptlabel, 7, 0, 1, 1)
        self.GPSAltitude = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSAltitude.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSAltitude.setReadOnly(True)
        self.GPSAltitude.setObjectName("GPSAltitude")
        self.GpsGridLayout.addWidget(self.GPSAltitude, 4, 2, 1, 1)
        self.Altitudelabel = QtGui.QLabel(self.GpsGroupBox)
        self.Altitudelabel.setObjectName("Altitudelabel")
        self.GpsGridLayout.addWidget(self.Altitudelabel, 4, 0, 1, 1)
        self.GPSEps = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSEps.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSEps.setReadOnly(True)
        self.GPSEps.setObjectName("GPSEps")
        self.GpsGridLayout.addWidget(self.GPSEps, 9, 2, 1, 1)
        self.Epslabel = QtGui.QLabel(self.GpsGroupBox)
        self.Epslabel.setObjectName("Epslabel")
        self.GpsGridLayout.addWidget(self.Epslabel, 9, 0, 1, 1)
        self.Lonlabel = QtGui.QLabel(self.GpsGroupBox)
        self.Lonlabel.setObjectName("Lonlabel")
        self.GpsGridLayout.addWidget(self.Lonlabel, 0, 3, 1, 1)
        self.GPSlon = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSlon.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSlon.setReadOnly(True)
        self.GPSlon.setObjectName("GPSlon")
        self.GpsGridLayout.addWidget(self.GPSlon, 0, 4, 1, 1)
        self.Speedlabel = QtGui.QLabel(self.GpsGroupBox)
        self.Speedlabel.setObjectName("Speedlabel")
        self.GpsGridLayout.addWidget(self.Speedlabel, 4, 3, 1, 1)
        self.GPSSpeed = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSSpeed.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSSpeed.setReadOnly(True)
        self.GPSSpeed.setObjectName("GPSSpeed")
        self.GpsGridLayout.addWidget(self.GPSSpeed, 4, 4, 1, 1)
        self.GPSClimb = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSClimb.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSClimb.setReadOnly(True)
        self.GPSClimb.setObjectName("GPSClimb")
        self.GpsGridLayout.addWidget(self.GPSClimb, 5, 4, 1, 1)
        self.Climblabel = QtGui.QLabel(self.GpsGroupBox)
        self.Climblabel.setObjectName("Climblabel")
        self.GpsGridLayout.addWidget(self.Climblabel, 5, 3, 1, 1)
        self.GPSEpc = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSEpc.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSEpc.setReadOnly(True)
        self.GPSEpc.setObjectName("GPSEpc")
        self.GpsGridLayout.addWidget(self.GPSEpc, 9, 4, 1, 1)
        self.Epclabel = QtGui.QLabel(self.GpsGroupBox)
        self.Epclabel.setObjectName("Epclabel")
        self.GpsGridLayout.addWidget(self.Epclabel, 9, 3, 1, 1)
        self.GPSEpv = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSEpv.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSEpv.setReadOnly(True)
        self.GPSEpv.setObjectName("GPSEpv")
        self.GpsGridLayout.addWidget(self.GPSEpv, 6, 4, 1, 1)
        self.Epvlabel = QtGui.QLabel(self.GpsGroupBox)
        self.Epvlabel.setObjectName("Epvlabel")
        self.GpsGridLayout.addWidget(self.Epvlabel, 6, 3, 1, 1)
        self.Ephlabel = QtGui.QLabel(self.GpsGroupBox)
        self.Ephlabel.setObjectName("Ephlabel")
        self.GpsGridLayout.addWidget(self.Ephlabel, 6, 0, 1, 1)
        self.GPSEph = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSEph.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSEph.setReadOnly(True)
        self.GPSEph.setObjectName("GPSEph")
        self.GpsGridLayout.addWidget(self.GPSEph, 6, 2, 1, 1)
        self.Tracklabel = QtGui.QLabel(self.GpsGroupBox)
        self.Tracklabel.setObjectName("Tracklabel")
        self.GpsGridLayout.addWidget(self.Tracklabel, 5, 0, 1, 1)
        self.GPSTrack = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSTrack.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSTrack.setReadOnly(True)
        self.GPSTrack.setObjectName("GPSTrack")
        self.GpsGridLayout.addWidget(self.GPSTrack, 5, 2, 1, 1)
        self.Epdlabel = QtGui.QLabel(self.GpsGroupBox)
        self.Epdlabel.setObjectName("Epdlabel")
        self.GpsGridLayout.addWidget(self.Epdlabel, 7, 3, 1, 1)
        self.GPSEpd = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSEpd.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSEpd.setReadOnly(True)
        self.GPSEpd.setObjectName("GPSEpd")
        self.GpsGridLayout.addWidget(self.GPSEpd, 7, 4, 1, 1)
        self.Datelabel = QtGui.QLabel(self.GpsGroupBox)
        self.Datelabel.setObjectName("Datelabel")
        self.GpsGridLayout.addWidget(self.Datelabel, 2, 0, 1, 1)
        self.Utclabel = QtGui.QLabel(self.GpsGroupBox)
        self.Utclabel.setObjectName("Utclabel")
        self.GpsGridLayout.addWidget(self.Utclabel, 2, 3, 1, 1)
        self.GPSUtctime = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSUtctime.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSUtctime.setReadOnly(True)
        self.GPSUtctime.setObjectName("GPSUtctime")
        self.GpsGridLayout.addWidget(self.GPSUtctime, 2, 4, 1, 1)
        self.GPSTime = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSTime.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSTime.setReadOnly(True)
        self.GPSTime.setObjectName("GPSTime")
        self.GpsGridLayout.addWidget(self.GPSTime, 2, 2, 1, 1)
        self.GPSPdop = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSPdop.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSPdop.setReadOnly(True)
        self.GPSPdop.setObjectName("GPSPdop")
        self.GpsGridLayout.addWidget(self.GPSPdop, 0, 6, 1, 1)
        self.Pdoplabel = QtGui.QLabel(self.GpsGroupBox)
        self.Pdoplabel.setObjectName("Pdoplabel")
        self.GpsGridLayout.addWidget(self.Pdoplabel, 0, 5, 1, 1)
        self.GPSHdop = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSHdop.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSHdop.setReadOnly(True)
        self.GPSHdop.setObjectName("GPSHdop")
        self.GpsGridLayout.addWidget(self.GPSHdop, 2, 6, 1, 1)
        self.GPSVdop = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSVdop.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSVdop.setReadOnly(True)
        self.GPSVdop.setObjectName("GPSVdop")
        self.GpsGridLayout.addWidget(self.GPSVdop, 4, 6, 1, 1)
        self.GPSTdop = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSTdop.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSTdop.setReadOnly(True)
        self.GPSTdop.setObjectName("GPSTdop")
        self.GpsGridLayout.addWidget(self.GPSTdop, 5, 6, 1, 1)
        self.GPSGdop = QtGui.QLineEdit(self.GpsGroupBox)
        self.GPSGdop.setAlignment(QtCore.Qt.AlignCenter)
        self.GPSGdop.setReadOnly(True)
        self.GPSGdop.setObjectName("GPSGdop")
        self.GpsGridLayout.addWidget(self.GPSGdop, 6, 6, 1, 1)
        self.Hdoplabel = QtGui.QLabel(self.GpsGroupBox)
        self.Hdoplabel.setObjectName("Hdoplabel")
        self.GpsGridLayout.addWidget(self.Hdoplabel, 2, 5, 1, 1)
        self.Vdoplabel = QtGui.QLabel(self.GpsGroupBox)
        self.Vdoplabel.setObjectName("Vdoplabel")
        self.GpsGridLayout.addWidget(self.Vdoplabel, 4, 5, 1, 1)
        self.Tdoplabel = QtGui.QLabel(self.GpsGroupBox)
        self.Tdoplabel.setObjectName("Tdoplabel")
        self.GpsGridLayout.addWidget(self.Tdoplabel, 5, 5, 1, 1)
        self.Gdoplabel = QtGui.QLabel(self.GpsGroupBox)
        self.Gdoplabel.setObjectName("Gdoplabel")
        self.GpsGridLayout.addWidget(self.Gdoplabel, 6, 5, 1, 1)
        self.StartGps = QtGui.QPushButton(self.GpsGroupBox)
        self.StartGps.setCheckable(True)
        self.StartGps.setObjectName("StartGps")
        self.GpsGridLayout.addWidget(self.StartGps, 9, 6, 1, 1)
        self.GPSSend = QtGui.QCheckBox(self.GpsGroupBox)
        self.GPSSend.setObjectName("GPSSend")
        self.GpsGridLayout.addWidget(self.GPSSend, 7, 6, 1, 1)
        self.verticalLayout_20.addLayout(self.GpsGridLayout)
        self.verticalLayout.addWidget(self.GpsGroupBox)

        self.retranslateUi(Form)
        self.tabWidget_2.setCurrentIndex(1)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        Form.setWindowTitle(QtGui.QApplication.translate("Form", "GPS", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget_2.setTabText(self.tabWidget_2.indexOf(self.tab_5), QtGui.QApplication.translate("Form", "Graph", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget_2.setTabText(self.tabWidget_2.indexOf(self.tab_6), QtGui.QApplication.translate("Form", "Map", None, QtGui.QApplication.UnicodeUTF8))
        self.Latlabel.setText(QtGui.QApplication.translate("Form", "Lat", None, QtGui.QApplication.UnicodeUTF8))
        self.Eptlabel.setText(QtGui.QApplication.translate("Form", "Ept", None, QtGui.QApplication.UnicodeUTF8))
        self.Altitudelabel.setText(QtGui.QApplication.translate("Form", "Altitude", None, QtGui.QApplication.UnicodeUTF8))
        self.Epslabel.setText(QtGui.QApplication.translate("Form", "Eps", None, QtGui.QApplication.UnicodeUTF8))
        self.Lonlabel.setText(QtGui.QApplication.translate("Form", "Lon", None, QtGui.QApplication.UnicodeUTF8))
        self.Speedlabel.setText(QtGui.QApplication.translate("Form", "Speed", None, QtGui.QApplication.UnicodeUTF8))
        self.Climblabel.setText(QtGui.QApplication.translate("Form", "Climb", None, QtGui.QApplication.UnicodeUTF8))
        self.Epclabel.setText(QtGui.QApplication.translate("Form", "Epc", None, QtGui.QApplication.UnicodeUTF8))
        self.Epvlabel.setText(QtGui.QApplication.translate("Form", "Epv", None, QtGui.QApplication.UnicodeUTF8))
        self.Ephlabel.setText(QtGui.QApplication.translate("Form", "Eph", None, QtGui.QApplication.UnicodeUTF8))
        self.Tracklabel.setText(QtGui.QApplication.translate("Form", "Track", None, QtGui.QApplication.UnicodeUTF8))
        self.Epdlabel.setText(QtGui.QApplication.translate("Form", "Epd", None, QtGui.QApplication.UnicodeUTF8))
        self.Datelabel.setText(QtGui.QApplication.translate("Form", "Date", None, QtGui.QApplication.UnicodeUTF8))
        self.Utclabel.setText(QtGui.QApplication.translate("Form", "UTC", None, QtGui.QApplication.UnicodeUTF8))
        self.Pdoplabel.setText(QtGui.QApplication.translate("Form", "Pdop", None, QtGui.QApplication.UnicodeUTF8))
        self.Hdoplabel.setText(QtGui.QApplication.translate("Form", "Hdop", None, QtGui.QApplication.UnicodeUTF8))
        self.Vdoplabel.setText(QtGui.QApplication.translate("Form", "Vdop", None, QtGui.QApplication.UnicodeUTF8))
        self.Tdoplabel.setText(QtGui.QApplication.translate("Form", "Tdop", None, QtGui.QApplication.UnicodeUTF8))
        self.Gdoplabel.setText(QtGui.QApplication.translate("Form", "Gdop", None, QtGui.QApplication.UnicodeUTF8))
        self.StartGps.setText(QtGui.QApplication.translate("Form", "Start/Stop ", None, QtGui.QApplication.UnicodeUTF8))
        self.GPSSend.setText(QtGui.QApplication.translate("Form", "SendPosition", None, QtGui.QApplication.UnicodeUTF8))

from PyQt4 import QtWebKit
import images_rc
