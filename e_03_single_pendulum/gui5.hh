// Mainframe macro generated from application: C:\root\root_v6_24_00_win\bin\root.exe
// By ROOT version 6.24/00 on 2021-05-31 19:16:57
#pragma  once
#ifndef ROOT_TGDockableFrame
#include "TGDockableFrame.h"
#endif
#ifndef ROOT_TGMdiDecorFrame
#include "TGMdiDecorFrame.h"
#endif
#ifndef ROOT_TG3DLine
#include "TG3DLine.h"
#endif
#ifndef ROOT_TGMdiFrame
#include "TGMdiFrame.h"
#endif
#ifndef ROOT_TGMdiMainFrame
#include "TGMdiMainFrame.h"
#endif
#ifndef ROOT_TGMdiMenu
#include "TGMdiMenu.h"
#endif
#ifndef ROOT_TGListBox
#include "TGListBox.h"
#endif
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TGScrollBar
#include "TGScrollBar.h"
#endif
#ifndef ROOT_TGComboBox
#include "TGComboBox.h"
#endif
#ifndef ROOT_TGuiBldHintsEditor
#include "TGuiBldHintsEditor.h"
#endif
#ifndef ROOT_TRootBrowser
#include "TRootBrowser.h"
#endif
#ifndef ROOT_TGuiBldNameFrame
#include "TGuiBldNameFrame.h"
#endif
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGMenu
#include "TGMenu.h"
#endif
#ifndef ROOT_TGFileDialog
#include "TGFileDialog.h"
#endif
#ifndef ROOT_TGShutter
#include "TGShutter.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#ifndef ROOT_TGCommandPlugin
#include "TGCommandPlugin.h"
#endif
#ifndef ROOT_TGCanvas
#include "TGCanvas.h"
#endif
#ifndef ROOT_TGFSContainer
#include "TGFSContainer.h"
#endif
#ifndef ROOT_TGuiBldEditor
#include "TGuiBldEditor.h"
#endif
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
#endif
#ifndef ROOT_TGTextEdit
#include "TGTextEdit.h"
#endif
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TRootContextMenu
#include "TRootContextMenu.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TGView
#include "TGView.h"
#endif
#ifndef ROOT_TGMsgBox
#include "TGMsgBox.h"
#endif
#ifndef ROOT_TRootGuiBuilder
#include "TRootGuiBuilder.h"
#endif
#ifndef ROOT_TGFileBrowser
#include "TGFileBrowser.h"
#endif
#ifndef ROOT_TGTab
#include "TGTab.h"
#endif
#ifndef ROOT_TGListView
#include "TGListView.h"
#endif
#ifndef ROOT_TGSplitter
#include "TGSplitter.h"
#endif
#ifndef ROOT_TGTextEditor
#include "TGTextEditor.h"
#endif
#ifndef ROOT_TRootCanvas
#include "TRootCanvas.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGListTree
#include "TGListTree.h"
#endif
#ifndef ROOT_TGuiBldGeometryFrame
#include "TGuiBldGeometryFrame.h"
#endif
#ifndef ROOT_TGToolTip
#include "TGToolTip.h"
#endif
#ifndef ROOT_TGToolBar
#include "TGToolBar.h"
#endif
#ifndef ROOT_TRootEmbeddedCanvas
#include "TRootEmbeddedCanvas.h"
#endif
#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif
#ifndef ROOT_TGuiBldDragManager
#include "TGuiBldDragManager.h"
#endif
#ifndef ROOT_TGHtmlBrowser
#include "TGHtmlBrowser.h"
#endif

#include "Riostream.h"

class gui5 {
public:

    TGMainFrame* fMainFrame4763;
    TGHorizontalFrame* fHorizontalFrame4313;
    TGVerticalFrame* fVerticalFrame4318;
    TGTextButton* fTextButton4403;
    TGTextButton* fTextButton4410;
    TGComboBox* fComboBox4524;
    TGListBox* fListBox4548;
    TGVerticalFrame* fVerticalFrame4325;
    TRootEmbeddedCanvas* fRootEmbeddedCanvas4332;
	
	
    TCanvas* c134;
    TRootEmbeddedCanvas* fRootEmbeddedCanvas4371;
    TCanvas* c135;
    gui5()
    {

        // main frame
        fMainFrame4763 = new TGMainFrame(gClient->GetRoot(), 10, 10, kMainFrame | kVerticalFrame);
        fMainFrame4763->SetName("fMainFrame4763");

        // horizontal frame
        fHorizontalFrame4313 = new TGHorizontalFrame(fMainFrame4763, 488, 370, kHorizontalFrame);
        fHorizontalFrame4313->SetName("fHorizontalFrame4313");

        // vertical frame
        fVerticalFrame4318 = new TGVerticalFrame(fHorizontalFrame4313, 106, 366, kVerticalFrame);
        fVerticalFrame4318->SetName("fVerticalFrame4318");
        fTextButton4403 = new TGTextButton(fVerticalFrame4318, "fTextButton4403", -1, TGTextButton::GetDefaultGC()(), TGTextButton::GetDefaultFontStruct(), kRaisedFrame);
        fTextButton4403->SetTextJustify(36);
        fTextButton4403->SetMargins(0, 0, 0, 0);
        fTextButton4403->SetWrapLength(-1);
        fTextButton4403->Resize(96, 22);
        fVerticalFrame4318->AddFrame(fTextButton4403, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));
        fTextButton4410 = new TGTextButton(fVerticalFrame4318, "fTextButton4410", -1, TGTextButton::GetDefaultGC()(), TGTextButton::GetDefaultFontStruct(), kRaisedFrame);
        fTextButton4410->SetTextJustify(36);
        fTextButton4410->SetMargins(0, 0, 0, 0);
        fTextButton4410->SetWrapLength(-1);
        fTextButton4410->Resize(96, 22);
        fVerticalFrame4318->AddFrame(fTextButton4410, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));

        ULong_t ucolor;        // will reflect user color changes
        gClient->GetColorByName("#ffffff", ucolor);

        // combo box
        fComboBox4524 = new TGComboBox(fVerticalFrame4318, -1, kHorizontalFrame | kSunkenFrame | kOwnBackground);
        fComboBox4524->SetName("fComboBox4524");
        fComboBox4524->AddEntry("Entry 1 ", 0);
        fComboBox4524->AddEntry("Entry 2 ", 1);
        fComboBox4524->AddEntry("Entry 3 ", 2);
        fComboBox4524->AddEntry("Entry 4 ", 3);
        fComboBox4524->AddEntry("Entry 5 ", 4);
        fComboBox4524->AddEntry("Entry 6 ", 5);
        fComboBox4524->AddEntry("Entry 7 ", 6);
        fComboBox4524->Resize(102, 22);
        fComboBox4524->Select(-1);
        fVerticalFrame4318->AddFrame(fComboBox4524, new TGLayoutHints(kLHintsLeft | kLHintsTop, 2, 2, 2, 2));

        // list box
        fListBox4548 = new TGListBox(fVerticalFrame4318, -1, kSunkenFrame);
        fListBox4548->SetName("fListBox4548");
        fListBox4548->AddEntry("Entry 1", 0);
        fListBox4548->AddEntry("Entry 2", 1);
        fListBox4548->AddEntry("Entry 3", 2);
        fListBox4548->AddEntry("Entry 4", 3);
        fListBox4548->AddEntry("Entry 5", 4);
        fListBox4548->AddEntry("Entry 6", 5);
        fListBox4548->AddEntry("Entry 7", 6);
        fListBox4548->Resize(102, 274);
        fVerticalFrame4318->AddFrame(fListBox4548, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY, 2, 2, 2, 2));

        fHorizontalFrame4313->AddFrame(fVerticalFrame4318, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY, 2, 2, 2, 2));

        // vertical frame
        fVerticalFrame4325 = new TGVerticalFrame(fHorizontalFrame4313, 374, 366, kVerticalFrame);
        fVerticalFrame4325->SetName("fVerticalFrame4325");

        // embedded canvas
        fRootEmbeddedCanvas4332 = new TRootEmbeddedCanvas(0, fVerticalFrame4325, 370, 102, kSunkenFrame);
        fRootEmbeddedCanvas4332->SetName("fRootEmbeddedCanvas4332");
        Int_t wfRootEmbeddedCanvas4332 = fRootEmbeddedCanvas4332->GetCanvasWindowId();
        c134 = new TCanvas("c134", 10, 10, wfRootEmbeddedCanvas4332);
        fRootEmbeddedCanvas4332->AdoptCanvas(c134);
        fVerticalFrame4325->AddFrame(fRootEmbeddedCanvas4332, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));

        // embedded canvas
        fRootEmbeddedCanvas4371 = new TRootEmbeddedCanvas(0, fVerticalFrame4325, 370, 256, kSunkenFrame);
        fRootEmbeddedCanvas4371->SetName("fRootEmbeddedCanvas4371");
        Int_t wfRootEmbeddedCanvas4371 = fRootEmbeddedCanvas4371->GetCanvasWindowId();
        c135 = new TCanvas("c135", 10, 10, wfRootEmbeddedCanvas4371);
        fRootEmbeddedCanvas4371->AdoptCanvas(c135);
        fVerticalFrame4325->AddFrame(fRootEmbeddedCanvas4371, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

        fHorizontalFrame4313->AddFrame(fVerticalFrame4325, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

        fMainFrame4763->AddFrame(fHorizontalFrame4313, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1));

        fMainFrame4763->SetMWMHints(kMWMDecorAll,
            kMWMFuncAll,
            kMWMInputModeless);
        fMainFrame4763->MapSubwindows();

        fMainFrame4763->Resize(fMainFrame4763->GetDefaultSize());
        fMainFrame4763->MapWindow();
        fMainFrame4763->Resize(490, 372);
    }
};