import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    title: "Baby Keyboard Smasher!"
    color: "#456"
    property real defaultSpacing: 10

    property Splash splash: Splash {
        onTimeout: mainWindow.show()
    }

    component Splash: Window {

        id: splash
        flags: Qt.SplashScreen
        color: "transparent"
        modality: Qt.ApplicationModal
        title: "Baby Keyboard Smasher! 0.1.0"
        visible: true

        x: (Screen.width - splashImage.width) / 2
        y: (Screen.height - splashImage.height) / 2
        width: splashImage.width
        height: splashImage.height

        property int timeoutInterval: 2000
        signal timeout

        Image {
            id: splashImage
            source: "qrc:/images/ui/images/game-logo.png"
        }

        TapHandler {
            onTapped: splash.timeout()
        }

        Timer {
            interval: splash.timeoutInterval; running: true; repeat: false
            onTriggered: {
                splash.visible = false
                splash.timeout()
            }
        }
    }
}
