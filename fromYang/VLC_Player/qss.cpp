#include "qss.h"

// 按钮的基本样式，包括字体、颜色和边框
string button_qss = R"(
                   QPushButton
                   {
                       font:18px "黑体";
                       color:rgb(0,0,0);
                       border:none
                   }
                   QPushButton::menu-indicator:open
                   {
                       image:url(:/resources/down_arrow.svg);
                       subcontrol-position:right center;
                       subcontrol-origin:padding;border:none;
                   }
                   QPushButton::menu-indicator:closed
                   {
                       image:url(:/resources/up_arrow.svg);
                       subcontrol-position:right center;
                       subcontrol-origin:padding;border:none;
                   }
                   )";

// LOGO按钮的样式
string logo_button_qss = R"(
                         QPushButton
                         {
                             border:none;
                             font-family:黑体;
                             font-size:18px;
                             color:rgb(0,0,0);
                         }
                         QPushButton::menu-indicator:open
                         {
                             image:url(:/titlebar/resources/titleBar/down_arrow.svg);
                             subcontrol-position:right center;
                             subcontrol-origin:padding;border:none;
                         }
                         QPushButton::menu-indicator:closed
                         {
                             image:url(:/titlebar/resources/titleBar/up_arrow.svg);
                             subcontrol-position:right center;
                             subcontrol-origin:padding;border:none;
                         })";

// 定义了菜单的样式
string menu_qss = R"(
                  QMenu::item
                  {
                      font:16px "黑体";
                      color:rgb(0,0,0);
                      padding:8px 32px;
                      margin:0px 8px;
                      border-bottom:1px solid #DBDBDB;}/*选择项设置*/
                      QMenu::item:selected{background-color: #FFF8DC;
                  })";

// 定义了最小化模式按钮的样式
string minimode_qss = R"(
                      QPushButton
                      {
                          background-image:url(:/titlebar/resources/titleBar/minimode.svg);
                          border:none
                      }
                      QPushButton:hover
                      {
                          background-image:url(:/titlebar/resources/titleBar/minimode_hover.svg);
                          border:none;
                      }
                      )";

// 定义了置顶按钮的样式
string settop_qss = R"(
                    QPushButton
                    {
                        background-image:url(:/titlebar/resources/titleBar/settop.svg);
                        border:none
                    }
                    QPushButton:hover
                    {
                        background-color:rgb(240, 236, 220);
                        background-image:url(:/titlebar/resources/titleBar/settop_hover.svg);border:none;
                    }
                    )";

// 定义了最小化按钮的样式
string min_qss = R"(
                 QPushButton{background-image:url(:/titlebar/resources/titleBar/min.svg);border:none}
                 QPushButton:hover
                 {
                     background-image:url(:/titlebar/resources/titleBar/min_hover.svg);border:none;
                 })";

// 定义了最大化按钮的样式
string max_qss = R"(
                 QPushButton{background-image:url(:/titlebar/resources/titleBar/normal.svg);border:none}
                 QPushButton:hover
                 {
                     background-image:url(:/titlebar/resources/titleBar/normal_hover.svg);border:none;
                 }
                 )";

// 定义了关闭按钮的样式
string close_qss = R"(
                   QPushButton{background-image:url(:/titlebar/resources/titleBar/close.svg);border:none}
                   QPushButton:hover
                   {
                       background-image:url(:/titlebar/resources/titleBar/close_hover.svg);border:none;
                   }
                   )";

// 定义了滑块的样式
string slider_qss = R"(
                   QSlider:horizontal {
                       height: 8px;
                       background: transparent;
                       margin: 5px 0;
                   }
                   QSlider:vertical {
                       width: 8px;
                       background: transparent;
                       margin: 0 5px;
                   }
                   QSlider::groove:horizontal {
                       height: 4px;
                       background: #BBBBBB;
                       margin: 0 10px;
                       border-radius: 2px;
                   }
                   QSlider::groove:vertical {
                       width: 4px;
                       background: #BBBBBB;
                       margin: 10px 0;
                       border-radius: 2px;
                   }
                   QSlider::handle:horizontal {
                       width: 16px;
                       height: 16px;
                       background: black;
                       margin: -6px 0;
                       border-radius: 8px;
                   }
                   QSlider::handle:vertical {
                       width: 16px;
                       height: 16px;
                       background: black;
                       margin: 0 -6px;
                       border-radius: 8px;
                   }
                   QSlider::handle:horizontal:hover,
                   QSlider::handle:vertical:hover {
                       background: #333333;
                   }
                   QSlider::handle:horizontal:pressed,
                   QSlider::handle:vertical:pressed {
                       background: #555555;
                   }
                   )";

// 定义了时间显示标签的样式
string time_label_qss = R"(
                        QLabel {
                            font-family: "黑体";
                            font-size: 16px;
                            color: black;
                        }
                        )";
