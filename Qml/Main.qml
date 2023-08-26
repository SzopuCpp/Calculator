import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic
import Calculator 1.0

Window {

    //using using layout would be better instead of fixed size

    id: root
    title: "Calculator"
    visible: true

    width: 400
    minimumWidth: root.width
    maximumWidth: root.width

    height: 281
    minimumHeight: root.height
    maximumHeight: root.height
    
    FontLoader {
        id: output_font
        source: "qrc:/Resources/Fonts/Lato-Regular.ttf"
    }

    Calculator {
        id: calculator

        //A bit of a bad idea to send every key in C++ class
        //You should just pust all keys in to text
        //Next on press = just copy this string to calculator instance (and parse it), clear text and wait for result
        //when result happends - put result on text field
        //in this way application logick is simpler and we just separate GUI and calculation engine

    }

    Column {
        anchors.fill: parent
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#000000" //in QML we have named colors for simple colors
            visible: true
            height: 80
            width: 400

            Text {
                anchors.verticalCenter: parent.verticalCenter
                leftPadding: 10
                rightPadding: 10

                font.pointSize: 28
                font.family: output_font.name
                color: "#ffffff"
                text: calculator.text
            }
        }

        Rectangle {
            height: 1
            visible: true
            width: 400
            color: "#ffffff"
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: btn_negate
                text: "+/-"
                onClicked: calculator.Negate()

                Shortcut {
                    sequence: "n"
                    onActivated: btn_negate.onClicked()
                }
            }
            Button {
                id: btn_lparen
                text: "("
                onClicked: calculator.Append("(", Calculator.Parenthesis)

                Shortcut {
                    sequence: "("
                    onActivated: btn_lparen.onClicked()
                }
            }
            Button {
                id: btn_rparen
                text: ")"
                onClicked: calculator.Append(")", Calculator.Parenthesis)

                Shortcut {
                    sequence: ")"
                    onActivated: btn_rparen.onClicked()
                }
            }
            Button {
                id: btn_delete
                text: "<"
                onClicked: calculator.Delete()

                Shortcut {
                    sequence: "Backspace"
                    onActivated: btn_delete.onClicked()
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: btn_add
                text: "+"
                onClicked: calculator.Append("+", Calculator.Operator)

                Shortcut {
                    sequence: "+"
                    onActivated: btn_add.onClicked()
                }
            }
            Button {
                id: btn_seven
                text: "7"
                onClicked: calculator.Append("7")

                Shortcut {
                    sequence: "7"
                    onActivated: btn_seven.onClicked()
                }
            }
            Button {
                id: btn_eight
                text: "8"
                onClicked: calculator.Append("8")

                Shortcut {
                    sequence: "8"
                    onActivated: btn_eight.onClicked()
                }
            }
            Button {
                id: btn_nine
                text: "9"
                onClicked: calculator.Append("9")

                Shortcut {
                    sequence: "9"
                    onActivated: btn_nine.onClicked()
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: btn_subtract
                text: "-"
                onClicked: calculator.Append("-", Calculator.Operator)

                Shortcut {
                    sequence: "-"
                    onActivated: btn_subtract.onClicked()
                }
            }
            Button {
                id: btn_four
                text: "4"
                onClicked: calculator.Append("4")

                Shortcut {
                    sequence: "4"
                    onActivated: btn_four.onClicked()
                }
            }
            Button {
                id: btn_five
                text: "5"
                onClicked: calculator.Append("5")

                Shortcut {
                    sequence: "5"
                    onActivated: btn_five.onClicked()
                }
            }
            Button {
                id: btn_six
                text: "6"
                onClicked: calculator.Append("6")

                Shortcut {
                    sequence: "6"
                    onActivated: btn_six.onClicked()
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: btn_multiply
                text: "*"
                onClicked: calculator.Append("*", Calculator.Operator)

                Shortcut {
                    sequence: "*"
                    onActivated: btn_multiply.onClicked()
                }
            }
            Button {
                id: btn_one
                text: "1"
                onClicked: calculator.Append("1")

                Shortcut {
                    sequence: "1"
                    onActivated: btn_one.onClicked()
                }
            }
            Button {
                id: btn_two
                text: "2"
                onClicked: calculator.Append("2")

                Shortcut {
                    sequence: "2"
                    onActivated: btn_two.onClicked()
                }
            }
            Button {
                id: btn_three
                text: "3"
                onClicked: calculator.Append("3")

                Shortcut {
                    sequence: "3"
                    onActivated: btn_three.onClicked()
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: btn_divide
                text: "/"
                onClicked: calculator.Append("/", Calculator.Operator)

                Shortcut {
                    sequence: "/"
                    onActivated: btn_divide.onClicked()
                }
            }
            Button {
                id: btn_zero
                text: "0"
                onClicked: calculator.Append("0")

                Shortcut {
                    sequence: "0"
                    onActivated: btn_zero.onClicked()
                }
            }
            Button {
                id: btn_dot
                text: "."
                onClicked: calculator.Append(".", Calculator.Dot)

                Shortcut {
                    sequences: [".", ","]
                    onActivated: btn_dot.onClicked()
                }
            }
            Button {
                id: btn_calc
                text: "="
                onClicked: calculator.Calculate()

                Shortcut {
                    sequences: ["=", "Enter"]
                    onActivated: btn_calc.onClicked()
                }
            }
        }
    }
}
