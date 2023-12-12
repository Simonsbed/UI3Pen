#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::example::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
        flag = false;
        px = 100;
        py = 100;
        mySize = 16;
        ischecked = true;
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    

}

struct winrt::Windows::UI::Color myCol = winrt::Microsoft::UI::Colors::Green();
void winrt::example::implementation::MainWindow::MenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    vx.clear();
    vy.clear();
    col.clear();
    size.clear();
    flag = false;
    px = 100;
    py = 100;
    mySize = 16;
}


void winrt::example::implementation::MainWindow::MenuFlyoutItem_Click_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    FILE* fw;
    errno_t err;
    err = fopen_s(&fw, "C:/Users/MinKyu/source/repos/example/Save/my.text", "w");
    if (err == 0)
    {
        MessageBox(NULL, L"The File was opened\n", L"hi1", NULL);
        int num = vx.size();
        fprintf_s(fw, "%d\n", num);
        for (int i = 0; i < num; i++)
        {
            fprintf_s(fw, "%f %f %d %d %d %d %f\n", vx[i], vy[i], col[i].A, col[i].B, col[i].G, col[i].R, size[i]);
        }
        fclose(fw);
    }
    else MessageBox(NULL, L"The file was not opened\n", L"hi2", NULL);
}


void winrt::example::implementation::MainWindow::MenuFlyoutItem_Click_2(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    // Open for write
    FILE* fr;
    errno_t err;
    err = fopen_s(&fr, "C:/Users/MinKyu/source/repos/example/Save/my.text", "r");// +, ccs = UTF - 8");
    if (err == 0)
    {
        MessageBox(NULL, L"The file was opened\n", L"hi1", NULL);
        int num;

        float vx1, vy1, size1;
        unsigned char colA, colB, colG, colR;

        fscanf_s(fr, "%d", &num);
        for (int i = 0; i < num; i++) {
            fscanf_s(fr, "%f %f %hhu %hhu %hhu %hhu %f ", &vx1, &vy1, &colA, &colB, &colG, &colR, &size1);
            vx.push_back(vx1);
            vy.push_back(vy1);
            myCol.A = colA;
            myCol.B = colB;
            myCol.G = colG;
            myCol.R = colR;
            col.push_back(myCol);
            size.push_back(size1);
        }
        fclose(fr);
        MessageBox(NULL, L"The file closed\n", L"hi1", NULL);
        CanvasControl_PointerReleased(NULL, NULL);
    }
    else  MessageBox(NULL, L"The file was not opened\n", L"hi2", NULL);
}


void winrt::example::implementation::MainWindow::MenuFlyoutItem_Click_3(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    this->Close();
}


void winrt::example::implementation::MainWindow::Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    mySize = e.NewValue();
}


void winrt::example::implementation::MainWindow::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = true;
}


void winrt::example::implementation::MainWindow::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = false;
    px = py = 0.0;
    vx.push_back(px);
    vy.push_back(py);
    col.push_back(myCol);
    size.push_back(mySize);
}


void winrt::example::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    px = e.GetCurrentPoint(canvas).Position().X;
    py = e.GetCurrentPoint(canvas).Position().Y;
    if (flag) {
        vx.push_back(px);
        vy.push_back(py);
        col.push_back(myCol);
        size.push_back(mySize);
        canvas.Invalidate();
    }
}


void winrt::example::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    int n = vx.size();
    if (n <= 2) return;

    for (int i = 1; i < n; i++) {
        if (vx[i] == 0.0 && vy[i] == 0.0) {
            i++; continue;
        }
        args.DrawingSession().DrawLine(vx[i - 1], vy[i - 1], vx[i], vy[i], col[i], size[i]);
        args.DrawingSession().FillCircle(vx[i - 1], vy[i - 1], size[i] / 2, col[i]);
        args.DrawingSession().FillCircle(vx[i], vy[i], size[i] / 2, col[i]);
    }
    canvas.Invalidate();
}


void winrt::example::implementation::MainWindow::ColorPicker_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    if (ischecked)
    {
        ischecked = FALSE;
        ColorPicker().Label(L"Disable");
        colorPanel().Visibility(Visibility::Collapsed);
    }
    else
    {
        ischecked = TRUE;
        ColorPicker().Label(L"Enable");
        colorPanel().Visibility(Visibility::Visible);
    }
}


void winrt::example::implementation::MainWindow::ColorPicker_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    myCol = args.NewColor();
}
