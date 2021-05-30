#ifndef TGSignals_h__
#define TGSignals_h__
#include "RQSignals.hh"





START__DEFINE_RQ_SIGNAL_BASE_CLASS(TQObject)
  __DEFINE_RQ_SIGNAL__(Destroyed, "Destroyed()")
  __DEFINE_RQ_SIGNAL__(ChangedBy, "ChangedBy(char*)")
  __DEFINE_RQ_SIGNAL__(Message ,  "Message(char*)")
END__DEFINE_RQ_SIGNAL_CLASS(TQObject)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TApplication, TQObject)
    __DEFINE_RQ_SIGNAL__(HandleIdleTimer, "HandleIdleTimer()")
    __DEFINE_RQ_SIGNAL__(LineProcessed, "LineProcessed(const char*)")
    __DEFINE_RQ_SIGNAL__(Terminate, "Terminate(Int_t)")
    __DEFINE_RQ_SIGNAL__(KeyPressed, "KeyPressed(Int_t)")
    __DEFINE_RQ_SIGNAL__(ReturnPressed, "ReturnPressed(char*)")
END__DEFINE_RQ_SIGNAL_CLASS(TApplication)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TPad, TQObject)
    __DEFINE_RQ_SIGNAL__(RangeChanged,"RangeChanged()")
    __DEFINE_RQ_SIGNAL__(RangeAxisChanged , "RangeAxisChanged()")
    __DEFINE_RQ_SIGNAL__(EventPave,"EventPave()")
    __DEFINE_RQ_SIGNAL__(StartEditing, "StartEditing()")
    __DEFINE_RQ_SIGNAL__(Closed, "Closed()")
    __DEFINE_RQ_SIGNAL__(Modified, "Modified()")
    __DEFINE_RQ_SIGNAL__(RecordLatex, "RecordLatex(const TObject*)")
    __DEFINE_RQ_SIGNAL__(RecordPave, "RecordPave(const TObject*)")
END__DEFINE_RQ_SIGNAL_CLASS(TPad)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TCanvas, TPad)
  __DEFINE_RQ_SIGNAL__(Picked,"Picked(TPad*,TObject*,Int_t)")
  __DEFINE_RQ_SIGNAL__( ProcessedEvent, "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)") 
  __DEFINE_RQ_SIGNAL__( Selected, "Selected(TVirtualPad*,TObject*,Int_t)")
  __DEFINE_RQ_SIGNAL__(Cleared, "Cleared(TVirtualPad*)")
  __DEFINE_RQ_SIGNAL__(Closed, "Closed()")
END__DEFINE_RQ_SIGNAL_CLASS(TCanvas)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TEveDigitSet, TQObject)
  __DEFINE_RQ_SIGNAL__(SecSelected, "SecSelected(TEveDigitSet*, Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TEveDigitSet)



template <typename T>
class TGButton_signals :TPad_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGButton_signals, TPad_signals) {}
  __DEFINE_RQ_SIGNAL__(Pressed, "Pressed()")
  __DEFINE_RQ_SIGNAL__(Released, "Released()")
  __DEFINE_RQ_SIGNAL__(Clicked, "Clicked()")
  __DEFINE_RQ_SIGNAL__(Toggled, "Toggled(Bool_t)")
  __DEFINE_RQ_SIGNAL__(MBPressed, "MBPressed()")
  __DEFINE_RQ_SIGNAL__(MBReleased, "MBReleased()")
  __DEFINE_RQ_SIGNAL__(MBClicked, "MBClicked()")
  __DEFINE_RQ_SIGNAL__(ItemClicked, "ItemClicked(Int_t)")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGButton, TGButton_signals)

class TGButtonGroup;
template <typename T>
class TGButtonGroup_signals :TGButton_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGButtonGroup_signals, TGButton_signals) {}
  __DEFINE_RQ_SIGNAL__(Pressed, "Pressed(Int_t)")
  __DEFINE_RQ_SIGNAL__(Released,"Released(Int_t)")
  __DEFINE_RQ_SIGNAL__(Clicked,"Clicked(Int_t)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGButtonGroup, TGButton_signals)

class TGFrame;
template <typename T> 
class TGFrame_signals: public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGFrame_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(ProcessedConfigure,"ProcessedConfigure(Event_t*)")
    __DEFINE_RQ_SIGNAL__(ProcessedEvent,"ProcessedEvent(Event_t*)")
    __DEFINE_RQ_SIGNAL__(CloseWindow,"CloseWindow()")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGFrame,TGFrame_signals)

class TGCanvas;
template <typename T>
class TGCanvas_signals:public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGCanvas_signals, TGFrame_signals) {}
   __DEFINE_RQ_SIGNAL__(SelectAll,"SelectAll()")                                
  __DEFINE_RQ_SIGNAL__(UnSelectAll,"UnSelectAll()")
  __DEFINE_RQ_SIGNAL__(InvertSelection, "InvertSelection()")
     __DEFINE_RQ_SIGNAL__(CurrentChanged_int_int,"CurrentChanged(Int_t,Int_t)")
     __DEFINE_RQ_SIGNAL__(CurrentChanged_TGFrameStar,"CurrentChanged(TGFrame*)")
     __DEFINE_RQ_SIGNAL__(KeyPressed, "KeyPressed(TGFrame*,UInt_t,UInt_t)")
     __DEFINE_RQ_SIGNAL__(ReturnPressed,"ReturnPressed(TGFrame*)")
     __DEFINE_RQ_SIGNAL__(SpacePressed,"SpacePressed(TGFrame*)")
     __DEFINE_RQ_SIGNAL__(OnMouseOver,"OnMouseOver(TGFrame*)")
     __DEFINE_RQ_SIGNAL__(Clicked_TGFrameStar,"Clicked(TGFrame*,Int_t)")
     __DEFINE_RQ_SIGNAL__(Clicked_TGFrameStar_Int_t_Int_t_Int_t,"Clicked(TGFrame*,Int_t,Int_t,Int_t)")
     __DEFINE_RQ_SIGNAL__ (DoubleClicked_TGFrameStar_Int_t,"DoubleClicked(TGFrame*,Int_t)")
     __DEFINE_RQ_SIGNAL__(DoubleClicked_TGFrameStar_Int_t_Int_t_Int_t,"DoubleClicked(TGFrame*,Int_t,Int_t,Int_t)")
};


__DEFINE_RQ_SIGNAL__FACTORY(TGCanvas, TGCanvas_signals)



class TGClient;

template <typename T>
class TGClient_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGClient_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(RegisteredWindow,"RegisteredWindow(Window_t)")
  __DEFINE_RQ_SIGNAL__(ProcessedEvent, "ProcessedEvent(Event_t*, Window_t)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TGClient, TGClient_signals)



class TGColorDialog;
template <typename T>
class TGColorDialog_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGColorDialog_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(ColorSelected, "ColorSelected(Pixel_t)")
  __DEFINE_RQ_SIGNAL__(AlphaColorSelected, "AlphaColorSelected(ULong_t)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGColorDialog, TGColorDialog_signals)



class TGComboBox;
template <typename T>
class TGComboBox_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGComboBox_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(Selected_int_int, "Selected(Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected_int, "Selected(Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected_ccharStar, "Selected(char*)")
  __DEFINE_RQ_SIGNAL__(ReturnPressed,"ReturnPressed()")

};
__DEFINE_RQ_SIGNAL__FACTORY(TGComboBox, TGComboBox_signals)


class TGDockableFrame;
template <typename T>
class TGDockableFrame_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGDockableFrame_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(Docked,"Docked()")
  __DEFINE_RQ_SIGNAL__(Undocked, "Undocked()")


};
__DEFINE_RQ_SIGNAL__FACTORY(TGDockableFrame, TGDockableFrame_signals)

class TGDoubleSlider;

template <typename T>
class TGDoubleSlider_signals :public TGFrame_signals<T> {
public:
 __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGDoubleSlider_signals, TGFrame_signals) {}
 __DEFINE_RQ_SIGNAL__(PositionChanged,"PositionChanged()")
 __DEFINE_RQ_SIGNAL__(Pressed,"Pressed()")
 __DEFINE_RQ_SIGNAL__(Released,"Released()")


};
__DEFINE_RQ_SIGNAL__FACTORY(TGDoubleSlider, TGDoubleSlider_signals)



class TGedMarkerSelect;
template <typename T>
class TGedMarkerSelect_signals :public TGButton_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGedMarkerSelect_signals, TGButton_signals) {}
  __DEFINE_RQ_SIGNAL__(MarkerSelected,"MarkerSelected(Style_t)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGedMarkerSelect, TGedMarkerSelect_signals)

class TGedPatternSelect;
template <typename T>
class TGedPatternSelect_signals :public TGButton_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGedPatternSelect_signals, TGButton_signals) {}
  __DEFINE_RQ_SIGNAL__(PatternSelected, "PatternSelected(Style_t)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGedPatternSelect, TGedPatternSelect_signals)



class TGeoPconEditor;
template <typename T>
class TGeoPconEditor_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGeoPconEditor_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(Changed, "Changed(Int_t)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGeoPconEditor, TGeoPconEditor_signals)

class TGEventHandler;
template <typename T>
class TGEventHandler_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGEventHandler_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(ProcessedEvent, "ProcessedEvent(Event_t*)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGEventHandler, TGEventHandler_signals)



class TGFontDialog;
template <typename T>
class TGFontDialog_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGFontDialog_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(ProcessedEvent, "ProcessedEvent(Event_t*)")
  __DEFINE_RQ_SIGNAL__(FontSelected, "FontSelected(char*)")
  __DEFINE_RQ_SIGNAL__(AlignSelected,"AlignSelected(Int_t)")
  __DEFINE_RQ_SIGNAL__(ColorSelected , "ColorSelected(Pixel_t)")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGFontDialog, TGFontDialog_signals)



class TGHtml;
template <typename T>
class TGHtml_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGHtml_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(MouseOver, "MouseOver(const char *)")
  __DEFINE_RQ_SIGNAL__(MouseDown, "MouseDown(const char *)") 
  __DEFINE_RQ_SIGNAL__(ButtonClicked, "ButtonClicked(char*,char*)") 
  __DEFINE_RQ_SIGNAL__(SubmitClicked, "SubmitClicked(char*)")
  __DEFINE_RQ_SIGNAL__(CheckToggled,  "CheckToggled(char*,Bool_t,char*)" )
  __DEFINE_RQ_SIGNAL__(RadioChanged,  "RadioChanged(char*,char*)")
  __DEFINE_RQ_SIGNAL__(InputSelected, "InputSelected(char*,char*)")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGHtml, TGHtml_signals)


class TGHtmlBrowser;
template <typename T>
class TGHtmlBrowser_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGHtmlBrowser_signals, TGFrame_signals) {}
 __DEFINE_RQ_SIGNAL__(Clicked, "Clicked(char *)")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGHtmlBrowser, TGHtmlBrowser_signals)


class TGImageMap;
template <typename T>
class TGImageMap_signals :public TGButton_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGImageMap_signals, TGButton_signals) {}
  
  __DEFINE_RQ_SIGNAL__ (RegionClicked,  "RegionClicked(Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_Int_t, "DoubleClicked(Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked()")
  __DEFINE_RQ_SIGNAL__(OnMouseOver, "OnMouseOver(Int_t)")
  __DEFINE_RQ_SIGNAL__(OnMouseOut, "OnMouseOut(Int_t)")

  
  
};

__DEFINE_RQ_SIGNAL__FACTORY(TGImageMap, TGImageMap_signals)



class TGLClipSetEditor;
template <typename T>
class TGLClipSetEditor_signals :public TGButton_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGLClipSetEditor_signals, TGButton_signals) {}
  __DEFINE_RQ_SIGNAL__(Changed,"Changed()")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGLClipSetEditor, TGLClipSetEditor_signals)


class TGListBox;
template <typename T>
class TGListBox_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGListBox_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(SelectionChanged,"SelectionChanged()")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_int,"DoubleClicked(Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_int_int,"DoubleClicked(Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected_int,"Selected(Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected_int_int,"Selected(Int_t,Int_t)")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGListBox, TGListBox_signals)



class TGListTree;
template <typename T>
class TGListTree_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGListTree_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(MouseOver_TGListTreeItem,  "MouseOver(TGListTreeItem*)")
  __DEFINE_RQ_SIGNAL__(MouseOver_TGListTreeItemStar_UInt_t,  "MouseOver(TGListTreeItem*,UInt_t)" )
  __DEFINE_RQ_SIGNAL__(KeyPressed, "KeyPressed(TGListTreeItem*,ULong_t,ULong_t)" )
  __DEFINE_RQ_SIGNAL__(ReturnPressed,  "ReturnPressed(TGListTreeItem*)"     )
  __DEFINE_RQ_SIGNAL__(Clicked_TGListTreeItemStar_Int_t, "Clicked(TGListTreeItem*,Int_t)" )
  __DEFINE_RQ_SIGNAL__(Clicked_TGListTreeItemStar_Int_t_Int_t_Int_t, "Clicked(TGListTreeItem*,Int_t,Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(Clicked_TGListTreeItemStar_Int_t_UInt_t_Int_t_Int_t, "Clicked(TGListTreeItem*,Int_t,UInt_t,Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_TGListTreeItemStar_Int_t,  "DoubleClicked(TGListTreeItem*,Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_TGListTreeItemStar_Int_t_Int_t_Int_t,"DoubleClicked(TGListTreeItem*,Int_t,Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(Checked, "Checked(TObject*,Bool_t)" )
  __DEFINE_RQ_SIGNAL__(DataDropped,  "DataDropped(TGListTreeItem*,TDNDData*)" )

};

__DEFINE_RQ_SIGNAL__FACTORY(TGListTree, TGListTree_signals)



class TGListView;
template <typename T>
class TGListView_signals :public TGCanvas_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGListView_signals, TGCanvas_signals) {}
  __DEFINE_RQ_SIGNAL__(SelectionChanged,"SelectionChanged()")
  __DEFINE_RQ_SIGNAL__(Clicked_TGLVEntryStar_Int_t,"Clicked(TGLVEntry*,Int_t)")
    __DEFINE_RQ_SIGNAL__(Clicked_TGLVEntryStar_Int_t_Int_t_Int_t, "Clicked(TGLVEntry*,Int_t,Int_t,Int_t)")
    __DEFINE_RQ_SIGNAL__(DoubleClicked_TGLVEntryStar_Int_t,   "DoubleClicked(TGLVEntry*,Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_TGLVEntryStar_Int_t_Int_t_Int_t , "DoubleClicked(TGLVEntry*,Int_t,Int_t,Int_t)")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGListView, TGListView_signals)



class TGLOverlayButton;
template <typename T>
class TGLOverlayButton_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGLOverlayButton_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(Clicked, "Clicked(TGLViewerBase*)")
};

__DEFINE_RQ_SIGNAL__FACTORY(TGLOverlayButton, TGLOverlayButton_signals)


class TGLViewer;
template <typename T>
class TGLViewer_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGLViewer_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(Activated ,"Activated()")
  __DEFINE_RQ_SIGNAL__(DoubleClicked,"DoubleClicked()")
  __DEFINE_RQ_SIGNAL__(MouseIdle,"MouseIdle(TGLPhysicalShape*,UInt_t,UInt_t)" )
  __DEFINE_RQ_SIGNAL__(MouseOver_TGLPhysicalShapeStar,"MouseOver(TGLPhysicalShape*)")
  __DEFINE_RQ_SIGNAL__(MouseOver_TGLPhysicalShapeStar_UInt_t, "MouseOver(TGLPhysicalShape*,UInt_t)" )
  __DEFINE_RQ_SIGNAL__(MouseOver_TObjectStar_UInt_t, "MouseOver(TObject*,UInt_t)")
  __DEFINE_RQ_SIGNAL__(ReMouseOver,"ReMouseOver(TObject*,UInt_t)" )
  __DEFINE_RQ_SIGNAL__(UnMouseOver,"UnMouseOver(TObject*,UInt_t)" )
  __DEFINE_RQ_SIGNAL__(Clicked_TObjectStar,"Clicked(TObject*)")
  __DEFINE_RQ_SIGNAL__(Clicked_TObjectStar_UInt_t_UInt_t, "Clicked(TObject*,UInt_t,UInt_t)")
  __DEFINE_RQ_SIGNAL__(ReClicked, "ReClicked(TObject*,UInt_t,UInt_t)")
  __DEFINE_RQ_SIGNAL__(UnClicked, "UnClicked(TObject*,UInt_t,UInt_t)")

};

__DEFINE_RQ_SIGNAL__FACTORY(TGLViewer, TGLViewer_signals)

class TGMdiFrame;
template <typename T>
class TGMdiFrame_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGMdiFrame_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(CloseWindow, "CloseWindow()")


};

__DEFINE_RQ_SIGNAL__FACTORY(TGMdiFrame, TGMdiFrame_signals)


class TGMdiMainFrame;
template <typename T>
class TGMdiMainFrame_signals :public TGCanvas_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGMdiMainFrame_signals, TGCanvas_signals) {}
  __DEFINE_RQ_SIGNAL__(FrameCreated,"FrameCreated(Int_t)")
  __DEFINE_RQ_SIGNAL__(FrameClosed, "FrameClosed(Int_t)")
  __DEFINE_RQ_SIGNAL__(FrameMaximized, "FrameMaximized(Int_t)")
  __DEFINE_RQ_SIGNAL__(FrameMinimized, "FrameMinimized(Int_t)") 
  __DEFINE_RQ_SIGNAL__(FrameRestored, "FrameRestored(Int_t)")
  __DEFINE_RQ_SIGNAL__(FramesArranged, "FramesArranged(Int_t)")
  __DEFINE_RQ_SIGNAL__(SetCurrent, "SetCurrent(TGMdiFrame*)")

};

__DEFINE_RQ_SIGNAL__FACTORY(TGMdiMainFrame, TGMdiMainFrame_signals)




class TGPopupMenu;
template <typename T>
class TGPopupMenu_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGPopupMenu_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(PoppedUp, "PoppedUp()")
  __DEFINE_RQ_SIGNAL__(PoppedDown, "PoppedDown()")
    __DEFINE_RQ_SIGNAL__(Highlighted, "Highlighted(Int_t)")
    __DEFINE_RQ_SIGNAL__(Activated, "Activated(Int_t)")


};
__DEFINE_RQ_SIGNAL__FACTORY(TGPopupMenu, TGPopupMenu_signals)



class TGNumberEntry;

template <typename T>
class TGNumberEntry_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGNumberEntry_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(InvalidInput, "InvalidInput(char*)")
  __DEFINE_RQ_SIGNAL__(ValueChanged,  "ValueChanged(Long_t)")
  __DEFINE_RQ_SIGNAL__(ValueSet,"ValueSet(Long_t)")


};
__DEFINE_RQ_SIGNAL__FACTORY(TGNumberEntry, TGNumberEntry_signals)


class TGScrollBar;
template <typename T>
class TGScrollBar_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGScrollBar_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(PositionChanged, "PositionChanged(Int_t)") 
  __DEFINE_RQ_SIGNAL__(RangeChanged ,  "RangeChanged(Int_t)" )
  __DEFINE_RQ_SIGNAL__(PageSizeChanged, "PageSizeChanged(Int_t)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGScrollBar, TGScrollBar_signals)


class TGShutter;
template <typename T>
class TGShutter_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGShutter_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(Selected, " Selected()")
  __DEFINE_RQ_SIGNAL__(Selected_TGShutterItemStar, " Selected(TGShutterItem*)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGShutter, TGShutter_signals)


class TGSlider;
template <typename T>
class TGSlider_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGSlider_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(PositionChanged, "PositionChanged(Int_t)")
  __DEFINE_RQ_SIGNAL__(Pressed, "Pressed()")
  __DEFINE_RQ_SIGNAL__(Released ,"Released()")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGSlider, TGSlider_signals)




class TGSpeedo;
template <typename T>
class TGSpeedo_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGSpeedo_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(OdoClicked,"OdoClicked()")
  __DEFINE_RQ_SIGNAL__(LedClicked,"LedClicked()")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGSpeedo, TGSpeedo_signals)


class TGSplitFrame;
template <typename T>
class TGSplitFrame_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGSplitFrame_signals, TGFrame_signals) {}

 __DEFINE_RQ_SIGNAL__(Docked,"Docked(TGFrame*)" )
 __DEFINE_RQ_SIGNAL__(Undocked, "Undocked(TGFrame*)" )

};
__DEFINE_RQ_SIGNAL__FACTORY(TGSplitFrame, TGSplitFrame_signals)



class TGSplitter;
template <typename T>
class TGSplitter_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGSplitter_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(DragStarted,"DragStarted()" )
  __DEFINE_RQ_SIGNAL__(Moved, "Moved(Int_t)" )
  __DEFINE_RQ_SIGNAL__(LayoutHeader, "LayoutHeader(TGFrame*)")
  __DEFINE_RQ_SIGNAL__(LayoutListView, "LayoutListView()")
  __DEFINE_RQ_SIGNAL__(ButtonPressed, "ButtonPressed()")
  __DEFINE_RQ_SIGNAL__(ButtonReleased, "ButtonReleased()")
  __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked(TGVFileSplitter*)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TGSplitter, TGSplitter_signals)



class TGTab;
template <typename T>
class TGTab_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGTab_signals, TGFrame_signals) {}
__DEFINE_RQ_SIGNAL__(CloseTab,"CloseTab(Int_t)")
__DEFINE_RQ_SIGNAL__(Removed, "Removed(Int_t)")
__DEFINE_RQ_SIGNAL__(Selected , "Selected(Int_t)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TGTab, TGTab_signals)


class TGTextView;
template <typename T>
class TGTextView_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGTextView_signals, TGFrame_signals) {}

  __DEFINE_RQ_SIGNAL__(DataChanged, "DataChanged()")
  __DEFINE_RQ_SIGNAL__(DataDropped, "DataDropped(char *)")
  __DEFINE_RQ_SIGNAL__(Marked, "Marked(Bool_t)")
  __DEFINE_RQ_SIGNAL__(Clicked, "Clicked(char *)")
    __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked(char *)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGTextView, TGTextView_signals)

class TGTextEdit;
template <typename T>
class TGTextEdit_signals :public TGTextView_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGTextEdit_signals, TGTextView_signals) {}
  
  __DEFINE_RQ_SIGNAL__(FindAgain , "FindAgain()")
  __DEFINE_RQ_SIGNAL__(Closed, "Closed()")
  __DEFINE_RQ_SIGNAL__(Opened, "Opened()")
  __DEFINE_RQ_SIGNAL__(Saved, "Saved()")
  __DEFINE_RQ_SIGNAL__(SavedAs, "SavedAs()")
  

};
__DEFINE_RQ_SIGNAL__FACTORY(TGTextEdit, TGTextEdit_signals)

class TGSearchDialog;
template <typename T>
class TGSearchDialog_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGSearchDialog_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(TextEntered, "TextEntered(const char *)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGSearchDialog, TGSearchDialog_signals)


class TGTextEntry;
template <typename T>
class TGTextEntry_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGTextEntry_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(TextChanged, "TextChanged(char*)")
    __DEFINE_RQ_SIGNAL__(ReturnPressed, "ReturnPressed()")
    __DEFINE_RQ_SIGNAL__(TabPressed, "TabPressed()")
    __DEFINE_RQ_SIGNAL__(ShiftTabPressed, "ShiftTabPressed()")
    __DEFINE_RQ_SIGNAL__(CursorOutLeft, "CursorOutLeft()")
    __DEFINE_RQ_SIGNAL__(CursorOutRight, "CursorOutRight()")
    __DEFINE_RQ_SIGNAL__(CursorOutUp,  "CursorOutUp()")
    __DEFINE_RQ_SIGNAL__(CursorOutDown, "CursorOutDown()")
    __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked()")
};
__DEFINE_RQ_SIGNAL__FACTORY(TGTextEntry, TGTextEntry_signals)


class TGToolBar;
template <typename T>
class TGToolBar_signals :public TGFrame_signals<T> {
public:
 __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGToolBar_signals, TGFrame_signals) {}
 __DEFINE_RQ_SIGNAL__(Pressed, "Pressed(Int_t)")
 __DEFINE_RQ_SIGNAL__(Released, "Released(Int_t)")
 __DEFINE_RQ_SIGNAL__(Clicked , "Clicked(Int_t)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TGToolBar, TGToolBar_signals)


class TGToolTip;
template <typename T>
class TGToolTip_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGToolTip_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(Show, "Show(Int_t,Int_t)")
    __DEFINE_RQ_SIGNAL__(Hide, "Hide()")
    __DEFINE_RQ_SIGNAL__(Reset, "Reset()")

};
__DEFINE_RQ_SIGNAL__FACTORY(TGToolTip, TGToolTip_signals)


class TGuiBldEditor;
template <typename T>
class TGuiBldEditor_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TGuiBldEditor_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(UpdateSelected, "UpdateSelected(TGFrame*)")
  __DEFINE_RQ_SIGNAL__(ChangeSelected,  "ChangeSelected(TGFrame*)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TGuiBldEditor, TGuiBldEditor_signals)



class TMessageHandler;
template <typename T>
class TMessageHandler_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TMessageHandler_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(Added, "Added()")
  __DEFINE_RQ_SIGNAL__(Removed, "Removed()")
  __DEFINE_RQ_SIGNAL__(Notified, "Notified()")
};
__DEFINE_RQ_SIGNAL__FACTORY(TMessageHandler, TMessageHandler_signals)


class TMonitor;
template <typename T>
class TMonitor_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TMonitor_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(Ready, "Ready(TSocket*)")
};
__DEFINE_RQ_SIGNAL__FACTORY(TMonitor, TMonitor_signals)





class TProof;
template <typename T>
class TProof_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TProof_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(DisableGoAsyn, "DisableGoAsyn()")
    __DEFINE_RQ_SIGNAL__(Feedback, "Feedback(TList *objs)")
    __DEFINE_RQ_SIGNAL__(CloseProgressDialog,"CloseProgressDialog()")
    __DEFINE_RQ_SIGNAL__(QueryResultReady,"QueryResultReady(const char*)")
    __DEFINE_RQ_SIGNAL__(StopProcess,"StopProcess(Bool_t)")
    __DEFINE_RQ_SIGNAL__(CloseWindow, "CloseWindow()")
__DEFINE_RQ_SIGNAL__(LogMessage,"LogMessage(const char*,Bool_t)")
__DEFINE_RQ_SIGNAL__(Progress_Long64_t__Long64_t,"Progress(Long64_t,Long64_t)")
__DEFINE_RQ_SIGNAL__(Progress_Long64_t_Long64_t_Long64_t_Float_t_Float_t_Float_t_Float_t, "Progress(Long64_t,Long64_t,Long64_t,Float_t,Float_t,Float_t,Float_t)")
__DEFINE_RQ_SIGNAL__(ResetProgressDialog, "ResetProgressDialog(const char*,Int_t,Long64_t,Long64_t)")
__DEFINE_RQ_SIGNAL__(StartupMessage, "StartupMessage(const char*,Bool_t,Int_t,Int_t)")
__DEFINE_RQ_SIGNAL__(DataSetStatus, "DataSetStatus(const char*,Bool_t,Int_t,Int_t)")
__DEFINE_RQ_SIGNAL__(IsDataReady, "IsDataReady(Long64_t,Long64_t)")


};
__DEFINE_RQ_SIGNAL__FACTORY(TProof, TProof_signals)

class TQCommand;
template <typename T>
class TQCommand_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TQCommand_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(Redo, "Redo()")
  __DEFINE_RQ_SIGNAL__(Undo, "Undo()")
  __DEFINE_RQ_SIGNAL__(CurrentChanged,  "CurrentChanged(TQCommand*)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TQCommand, TQCommand_signals)

class TQConnection;
template <typename T>
class TQConnection_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TQConnection_signals, TQObject_signals) {}
  __DEFINE_RQ_SIGNAL__(Destroyed, "Destroyed()")

};
__DEFINE_RQ_SIGNAL__FACTORY(TQConnection, TQConnection_signals)

class TRootBrowser;
template <typename T>
class TRootBrowser_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TRootBrowser_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(BrowseObj, "BrowseObj(TObject*)")
    __DEFINE_RQ_SIGNAL__(ExecuteDefaultAction, "ExecuteDefaultAction(TObject*)")
    __DEFINE_RQ_SIGNAL__(DoubleClicked,  "DoubleClicked(TObject*)")
    __DEFINE_RQ_SIGNAL__(Checked, "Checked(TObject*,Bool_t)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TRootBrowser, TRootBrowser_signals)


class TRootBrowserLite;
template <typename T>
class TRootBrowserLite_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TRootBrowserLite_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(BrowseObj, "BrowseObj(TObject*)")
    __DEFINE_RQ_SIGNAL__(ExecuteDefaultAction, "ExecuteDefaultAction(TObject*)")
    __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked(TObject*)")
    __DEFINE_RQ_SIGNAL__(Checked, "Checked(TObject*,Bool_t)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TRootBrowserLite, TRootBrowserLite_signals)


class TNewChainDlg;
template <typename T>
class TNewChainDlg_signals :public TGFrame_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TNewChainDlg_signals, TGFrame_signals) {}
  __DEFINE_RQ_SIGNAL__(OnElementSelected, "OnElementSelected(TObject *)")

};
__DEFINE_RQ_SIGNAL__FACTORY(TNewChainDlg, TNewChainDlg_signals)


class TSysEvtHandler;
template <typename T>
class TSysEvtHandler_signals :public TQObject_signals<T> {
public:
  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(TSysEvtHandler_signals, TQObject_signals) {}
 __DEFINE_RQ_SIGNAL__(Activated,"Activated()")
   __DEFINE_RQ_SIGNAL__(DeActivated, "DeActivated()")
   __DEFINE_RQ_SIGNAL__(Notified, "Notified()")
   __DEFINE_RQ_SIGNAL__(Added, "Added()")
   __DEFINE_RQ_SIGNAL__(Removed, "Removed()")


};
__DEFINE_RQ_SIGNAL__FACTORY(TSysEvtHandler, TSysEvtHandler_signals)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TTimer, TSysEvtHandler)
    __DEFINE_RQ_SIGNAL__(TurnOn, "TurnOn()")
    __DEFINE_RQ_SIGNAL__(TurnOff, "TurnOff()")
    __DEFINE_RQ_SIGNAL__(Timeout ,"Timeout()")
END__DEFINE_RQ_SIGNAL_CLASS(TTimer)





#endif // TGSignals_h__
