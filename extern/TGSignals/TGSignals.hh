#ifndef TGSignals_h__
#define TGSignals_h__
#include "TImage.h"
#include "TApplication.h"
#include "RQSignals.hh"





START__DEFINE_RQ_SIGNAL_BASE_CLASS(TQObject)
  __DEFINE_RQ_SIGNAL__(Destroyed,      "Destroyed()"           )
  __DEFINE_RQ_SIGNAL__1(ChangedBy,      "ChangedBy(char*)" , char*)
  __DEFINE_RQ_SIGNAL__1(Message ,       "Message(char*)" , char*)
END__DEFINE_RQ_SIGNAL_CLASS(TQObject)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TApplication, TQObject)
    __DEFINE_RQ_SIGNAL__(HandleIdleTimer, "HandleIdleTimer()")
    __DEFINE_RQ_SIGNAL__1(LineProcessed, "LineProcessed(const char*)", const char*)
    __DEFINE_RQ_SIGNAL__1(Terminate, "Terminate(Int_t)", Int_t)
    __DEFINE_RQ_SIGNAL__1(KeyPressed, "KeyPressed(Int_t)", Int_t)
    __DEFINE_RQ_SIGNAL__1(ReturnPressed, "ReturnPressed(char*)", char*)
END__DEFINE_RQ_SIGNAL_CLASS(TApplication)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TPad, TQObject)
    __DEFINE_RQ_SIGNAL__(RangeChanged,"RangeChanged()")
    __DEFINE_RQ_SIGNAL__(RangeAxisChanged , "RangeAxisChanged()")
    __DEFINE_RQ_SIGNAL__(EventPave,"EventPave()")
    __DEFINE_RQ_SIGNAL__(StartEditing, "StartEditing()")
    __DEFINE_RQ_SIGNAL__(Closed, "Closed()")
    __DEFINE_RQ_SIGNAL__(Modified, "Modified()")
    __DEFINE_RQ_SIGNAL__1(RecordLatex, "RecordLatex(const TObject*)", const TObject*)
    __DEFINE_RQ_SIGNAL__1(RecordPave, "RecordPave(const TObject*)", const TObject*)
END__DEFINE_RQ_SIGNAL_CLASS(TPad)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TCanvas, TPad)
  __DEFINE_RQ_SIGNAL__1(Picked,"Picked(TPad*,TObject*,Int_t)", TPad*, TObject*, Int_t)
  __DEFINE_RQ_SIGNAL__1( ProcessedEvent, "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", Int_t, Int_t, Int_t, TObject*)
  __DEFINE_RQ_SIGNAL__1( Selected, "Selected(TVirtualPad*,TObject*,Int_t)", TVirtualPad*, TObject*, Int_t)
  __DEFINE_RQ_SIGNAL__1(Cleared, "Cleared(TVirtualPad*)", TVirtualPad*)
  __DEFINE_RQ_SIGNAL__(Closed, "Closed()")
END__DEFINE_RQ_SIGNAL_CLASS(TCanvas)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TEveDigitSet, TQObject)
  __DEFINE_RQ_SIGNAL__1(SecSelected, "SecSelected(TEveDigitSet*, Int_t)", TEveDigitSet*, Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TEveDigitSet)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGButton, TPad)
  __DEFINE_RQ_SIGNAL__(Pressed, "Pressed()")
  __DEFINE_RQ_SIGNAL__(Released, "Released()")
  __DEFINE_RQ_SIGNAL__(Clicked, "Clicked()")
  __DEFINE_RQ_SIGNAL__1(Toggled, "Toggled(Bool_t)", Bool_t)
  __DEFINE_RQ_SIGNAL__(MBPressed, "MBPressed()")
  __DEFINE_RQ_SIGNAL__(MBReleased, "MBReleased()")
  __DEFINE_RQ_SIGNAL__(MBClicked, "MBClicked()")
  __DEFINE_RQ_SIGNAL__1(ItemClicked, "ItemClicked(Int_t)", Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGButton)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGButtonGroup, TGButton)
  __DEFINE_RQ_SIGNAL__1(Pressed, "Pressed(Int_t)", Int_t)
  __DEFINE_RQ_SIGNAL__1(Released,"Released(Int_t)", Int_t)
  __DEFINE_RQ_SIGNAL__1(Clicked,"Clicked(Int_t)", Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGButtonGroup)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGFrame, TQObject)
  __DEFINE_RQ_SIGNAL__1(ProcessedConfigure,"ProcessedConfigure(Event_t*)", Event_t*)
  __DEFINE_RQ_SIGNAL__1(ProcessedEvent,"ProcessedEvent(Event_t*)", Event_t*)
  __DEFINE_RQ_SIGNAL__(CloseWindow,"CloseWindow()")
END__DEFINE_RQ_SIGNAL_CLASS(TGFrame)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGCanvas, TGFrame)
  __DEFINE_RQ_SIGNAL__(SelectAll,"SelectAll()")                                
  __DEFINE_RQ_SIGNAL__(UnSelectAll,"UnSelectAll()")
  __DEFINE_RQ_SIGNAL__(InvertSelection, "InvertSelection()")
  __DEFINE_RQ_SIGNAL__1(CurrentChanged_int_int,"CurrentChanged(Int_t,Int_t)", Int_t, Int_t)
  __DEFINE_RQ_SIGNAL__1(CurrentChanged,"CurrentChanged(TGFrame*)", TGFrame*)
  __DEFINE_RQ_SIGNAL__1(KeyPressed, "KeyPressed(TGFrame*,UInt_t,UInt_t)", TGFrame*, UInt_t, UInt_t)
  __DEFINE_RQ_SIGNAL__1(ReturnPressed,"ReturnPressed(TGFrame*)", TGFrame*)
  __DEFINE_RQ_SIGNAL__1(SpacePressed,"SpacePressed(TGFrame*)", TGFrame*)
  __DEFINE_RQ_SIGNAL__1(OnMouseOver,"OnMouseOver(TGFrame*)", TGFrame*)
  __DEFINE_RQ_SIGNAL__1(Clicked_TGFrameStar,"Clicked(TGFrame*,Int_t)", TGFrame*, Int_t)
  __DEFINE_RQ_SIGNAL__1(Clicked,"Clicked(TGFrame*,Int_t,Int_t,Int_t)", TGFrame*, Int_t, Int_t, Int_t)
  __DEFINE_RQ_SIGNAL__1(DoubleClicked_TGFrameStar_Int_t,"DoubleClicked(TGFrame*,Int_t)", TGFrame*, Int_t)
  __DEFINE_RQ_SIGNAL__1(DoubleClicked,"DoubleClicked(TGFrame*,Int_t,Int_t,Int_t)", TGFrame*, Int_t, Int_t, Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGCanvas)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGClient, TQObject)
  __DEFINE_RQ_SIGNAL__1(RegisteredWindow,"RegisteredWindow(Window_t)", Window_t)
  __DEFINE_RQ_SIGNAL__1(ProcessedEvent, "ProcessedEvent(Event_t*, Window_t)", Event_t*, Window_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGClient)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGColorDialog, TQObject)
__DEFINE_RQ_SIGNAL__1(ColorSelected, "ColorSelected(Pixel_t)", Pixel_t)
__DEFINE_RQ_SIGNAL__1(AlphaColorSelected, "AlphaColorSelected(ULong_t)", ULong_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGColorDialog)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGComboBox, TGFrame)
__DEFINE_RQ_SIGNAL__1(Selected_int_int, "Selected(Int_t,Int_t)", Int_t, Int_t)
__DEFINE_RQ_SIGNAL__1(Selected_int, "Selected(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(Selected_ccharStar, "Selected(char*)", char*)
__DEFINE_RQ_SIGNAL__(ReturnPressed, "ReturnPressed()")
END__DEFINE_RQ_SIGNAL_CLASS(TGComboBox)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGDockableFrame, TGFrame)
__DEFINE_RQ_SIGNAL__(Docked, "Docked()")
__DEFINE_RQ_SIGNAL__(Undocked, "Undocked()")
END__DEFINE_RQ_SIGNAL_CLASS(TGDockableFrame)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGDoubleSlider, TGFrame)
__DEFINE_RQ_SIGNAL__(PositionChanged, "PositionChanged()")
__DEFINE_RQ_SIGNAL__(Pressed, "Pressed()")
__DEFINE_RQ_SIGNAL__(Released, "Released()")
END__DEFINE_RQ_SIGNAL_CLASS(TGDoubleSlider)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGedMarkerSelect, TGButton)
__DEFINE_RQ_SIGNAL__1(MarkerSelected, "MarkerSelected(Style_t)", Style_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGedMarkerSelect)

START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGedPatternSelect, TGButton)
__DEFINE_RQ_SIGNAL__1(PatternSelected, "PatternSelected(Style_t)", Style_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGedPatternSelect)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGeoPconEditor, TGFrame)
__DEFINE_RQ_SIGNAL__1(Changed, "Changed(Int_t)", Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGeoPconEditor)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGEventHandler, TQObject)
__DEFINE_RQ_SIGNAL__1(ProcessedEvent, "ProcessedEvent(Event_t*)", Event_t*)
END__DEFINE_RQ_SIGNAL_CLASS(TGEventHandler)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGFontDialog, TGFrame)
__DEFINE_RQ_SIGNAL__1(ProcessedEvent, "ProcessedEvent(Event_t*)", Event_t*)
__DEFINE_RQ_SIGNAL__1(FontSelected, "FontSelected(char*)", char*)
__DEFINE_RQ_SIGNAL__1(AlignSelected, "AlignSelected(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(ColorSelected, "ColorSelected(Pixel_t)", Pixel_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGFontDialog)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGHtml, TGFrame)
__DEFINE_RQ_SIGNAL__1(MouseOver, "MouseOver(const char *)", const char*)
__DEFINE_RQ_SIGNAL__1(MouseDown, "MouseDown(const char *)", const char*)
__DEFINE_RQ_SIGNAL__1(ButtonClicked, "ButtonClicked(char*,char*)", char*, char*)
__DEFINE_RQ_SIGNAL__1(SubmitClicked, "SubmitClicked(char*)", char*)
__DEFINE_RQ_SIGNAL__1(CheckToggled, "CheckToggled(char*,Bool_t,char*)", char*, Bool_t, char*)
__DEFINE_RQ_SIGNAL__1(RadioChanged, "RadioChanged(char*,char*)", char*, char*)
__DEFINE_RQ_SIGNAL__1(InputSelected, "InputSelected(char*,char*)", char*, char*)
END__DEFINE_RQ_SIGNAL_CLASS(TGHtml)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGHtmlBrowser, TGFrame)
__DEFINE_RQ_SIGNAL__1(Clicked, "Clicked(char *)", char*)
END__DEFINE_RQ_SIGNAL_CLASS(TGHtmlBrowser)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGImageMap, TGButton)
__DEFINE_RQ_SIGNAL__1(RegionClicked, "RegionClicked(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(DoubleClicked_Int_t, "DoubleClicked(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked()")
__DEFINE_RQ_SIGNAL__1(OnMouseOver, "OnMouseOver(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(OnMouseOut, "OnMouseOut(Int_t)", Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGImageMap)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGLClipSetEditor, TGButton)
__DEFINE_RQ_SIGNAL__(Changed, "Changed()")
END__DEFINE_RQ_SIGNAL_CLASS(TGLClipSetEditor)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGListBox, TGFrame)
__DEFINE_RQ_SIGNAL__(SelectionChanged, "SelectionChanged()")
__DEFINE_RQ_SIGNAL__1(DoubleClicked_int, "DoubleClicked(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(DoubleClicked_int_int, "DoubleClicked(Int_t,Int_t)", Int_t, Int_t)
__DEFINE_RQ_SIGNAL__1(Selected_int, "Selected(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(Selected_int_int, "Selected(Int_t,Int_t)", Int_t, Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGListBox)

class TGListTreeItem;
class TDNDData;
START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGListTree, TGFrame)
__DEFINE_RQ_SIGNAL__1(MouseOver_TGListTreeItem, "MouseOver(TGListTreeItem*)", TGListTreeItem*)
__DEFINE_RQ_SIGNAL__1(MouseOver, "MouseOver(TGListTreeItem*,UInt_t)", TGListTreeItem*, UInt_t)
__DEFINE_RQ_SIGNAL__1(KeyPressed, "KeyPressed(TGListTreeItem*,ULong_t,ULong_t)", TGListTreeItem*, ULong_t, ULong_t)
__DEFINE_RQ_SIGNAL__1(ReturnPressed, "ReturnPressed(TGListTreeItem*)", TGListTreeItem*)
__DEFINE_RQ_SIGNAL__1(Clicked_TGListTreeItemStar_Int_t, "Clicked(TGListTreeItem*,Int_t)", TGListTreeItem*, Int_t)
__DEFINE_RQ_SIGNAL__1(Clicked_TGListTreeItemStar_Int_t_Int_t_Int_t, "Clicked(TGListTreeItem*,Int_t,Int_t,Int_t)", TGListTreeItem*, Int_t, Int_t, Int_t)
__DEFINE_RQ_SIGNAL__1(Clicked, "Clicked(TGListTreeItem*,Int_t,UInt_t,Int_t,Int_t)", TGListTreeItem*, Int_t, UInt_t, Int_t, Int_t)
__DEFINE_RQ_SIGNAL__1(DoubleClicked_TGListTreeItemStar_Int_t, "DoubleClicked(TGListTreeItem*,Int_t)", TGListTreeItem*, Int_t)
__DEFINE_RQ_SIGNAL__1(DoubleClicked, "DoubleClicked(TGListTreeItem*,Int_t,Int_t,Int_t)", TGListTreeItem*, Int_t, Int_t, Int_t)
__DEFINE_RQ_SIGNAL__1(Checked, "Checked(TObject*,Bool_t)", TObject*, Bool_t)
__DEFINE_RQ_SIGNAL__1(DataDropped, "DataDropped(TGListTreeItem*,TDNDData*)", TGListTreeItem*, TDNDData*)
END__DEFINE_RQ_SIGNAL_CLASS(TGListTree)


class TGLVEntry;
START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGListView, TGCanvas)
__DEFINE_RQ_SIGNAL__(SelectionChanged, "SelectionChanged()")
__DEFINE_RQ_SIGNAL__1(Clicked_TGLVEntryStar_Int_t, "Clicked(TGLVEntry*,Int_t)", TGLVEntry*, Int_t)
__DEFINE_RQ_SIGNAL__1(Clicked, "Clicked(TGLVEntry*,Int_t,Int_t,Int_t)", TGLVEntry*, Int_t, Int_t, Int_t)
__DEFINE_RQ_SIGNAL__1(DoubleClicked_TGLVEntryStar_Int_t, "DoubleClicked(TGLVEntry*,Int_t)", TGLVEntry*, Int_t)
__DEFINE_RQ_SIGNAL__1(DoubleClicked, "DoubleClicked(TGLVEntry*,Int_t,Int_t,Int_t)", TGLVEntry*, Int_t, Int_t, Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGListView)


class TGLViewerBase;
START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGLOverlayButton, TQObject)
__DEFINE_RQ_SIGNAL__1(Clicked, "Clicked(TGLViewerBase*)", TGLViewerBase*)
END__DEFINE_RQ_SIGNAL_CLASS(TGLOverlayButton)


class TGLPhysicalShape;
START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGLViewer, TQObject)
__DEFINE_RQ_SIGNAL__(Activated, "Activated()")
__DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked()")
__DEFINE_RQ_SIGNAL__1(MouseIdle, "MouseIdle(TGLPhysicalShape*,UInt_t,UInt_t)", TGLPhysicalShape*, UInt_t, UInt_t)
__DEFINE_RQ_SIGNAL__1(MouseOver_TGLPhysicalShapeStar, "MouseOver(TGLPhysicalShape*)", TGLPhysicalShape*)
__DEFINE_RQ_SIGNAL__1(MouseOver, "MouseOver(TGLPhysicalShape*,UInt_t)", TGLPhysicalShape*, UInt_t)
__DEFINE_RQ_SIGNAL__1(MouseOver_TObjectStar_UInt_t, "MouseOver(TObject*,UInt_t)", TObject*, UInt_t)
__DEFINE_RQ_SIGNAL__1(ReMouseOver, "ReMouseOver(TObject*,UInt_t)", TObject*, UInt_t)
__DEFINE_RQ_SIGNAL__1(UnMouseOver, "UnMouseOver(TObject*,UInt_t)", TObject*, UInt_t)
__DEFINE_RQ_SIGNAL__1(Clicked_TObjectStar, "Clicked(TObject*)", TObject*)
__DEFINE_RQ_SIGNAL__1(Clicked, "Clicked(TObject*,UInt_t,UInt_t)", TObject*, UInt_t, UInt_t)
__DEFINE_RQ_SIGNAL__1(ReClicked, "ReClicked(TObject*,UInt_t,UInt_t)", TObject*, UInt_t, UInt_t)
__DEFINE_RQ_SIGNAL__1(UnClicked, "UnClicked(TObject*,UInt_t,UInt_t)", TObject*, UInt_t, UInt_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGLViewer)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGMdiFrame, TGFrame)
__DEFINE_RQ_SIGNAL__(CloseWindow, "CloseWindow()")
END__DEFINE_RQ_SIGNAL_CLASS(TGMdiFrame)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGMdiMainFrame, TGCanvas)
__DEFINE_RQ_SIGNAL__1(FrameCreated, "FrameCreated(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(FrameClosed, "FrameClosed(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(FrameMaximized, "FrameMaximized(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(FrameMinimized, "FrameMinimized(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(FrameRestored, "FrameRestored(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(FramesArranged, "FramesArranged(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(SetCurrent, "SetCurrent(TGMdiFrame*)", TGMdiFrame*)
END__DEFINE_RQ_SIGNAL_CLASS(TGMdiMainFrame)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGPopupMenu, TGFrame)
__DEFINE_RQ_SIGNAL__(PoppedUp, "PoppedUp()")
__DEFINE_RQ_SIGNAL__(PoppedDown, "PoppedDown()")
__DEFINE_RQ_SIGNAL__1(Highlighted, "Highlighted(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(Activated, "Activated(Int_t)", Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGPopupMenu)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGNumberEntry, TGFrame)
__DEFINE_RQ_SIGNAL__1(InvalidInput, "InvalidInput(char*)", char*)
__DEFINE_RQ_SIGNAL__1(ValueChanged, "ValueChanged(Long_t)", Long_t)
__DEFINE_RQ_SIGNAL__1(ValueSet, "ValueSet(Long_t)", Long_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGNumberEntry)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGScrollBar, TGFrame)
__DEFINE_RQ_SIGNAL__1(PositionChanged, "PositionChanged(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(RangeChanged, "RangeChanged(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(PageSizeChanged, "PageSizeChanged(Int_t)", Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGScrollBar)

class TGShutterItem;
START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGShutter, TGFrame)
__DEFINE_RQ_SIGNAL__(Selected, " Selected()")
__DEFINE_RQ_SIGNAL__1(Selected_TGShutterItemStar, "Selected(TGShutterItem*)", TGShutterItem*)
END__DEFINE_RQ_SIGNAL_CLASS(TGShutter)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSlider, TGFrame)
__DEFINE_RQ_SIGNAL__1(PositionChanged, "PositionChanged(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__(Pressed, "Pressed()")
__DEFINE_RQ_SIGNAL__(Released, "Released()")
END__DEFINE_RQ_SIGNAL_CLASS(TGSlider)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSpeedo, TGFrame)
__DEFINE_RQ_SIGNAL__(OdoClicked, "OdoClicked()")
__DEFINE_RQ_SIGNAL__(LedClicked, "LedClicked()")
END__DEFINE_RQ_SIGNAL_CLASS(TGSpeedo)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSplitFrame, TGFrame)
__DEFINE_RQ_SIGNAL__1(Docked, "Docked(TGFrame*)", TGFrame*)
__DEFINE_RQ_SIGNAL__1(Undocked, "Undocked(TGFrame*)", TGFrame*)
END__DEFINE_RQ_SIGNAL_CLASS(TGSplitFrame)


class TGVFileSplitter;
START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSplitter, TGFrame)
__DEFINE_RQ_SIGNAL__(DragStarted, "DragStarted()")
__DEFINE_RQ_SIGNAL__1(Moved, "Moved(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(LayoutHeader, "LayoutHeader(TGFrame*)", TGFrame*)
__DEFINE_RQ_SIGNAL__(LayoutListView, "LayoutListView()")
__DEFINE_RQ_SIGNAL__(ButtonPressed, "ButtonPressed()")
__DEFINE_RQ_SIGNAL__(ButtonReleased, "ButtonReleased()")
__DEFINE_RQ_SIGNAL__1(DoubleClicked, "DoubleClicked(TGVFileSplitter*)", TGVFileSplitter*)
END__DEFINE_RQ_SIGNAL_CLASS(TGSplitter)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGTab, TGFrame)
__DEFINE_RQ_SIGNAL__1(CloseTab, "CloseTab(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(Removed, "Removed(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(Selected, "Selected(Int_t)", Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGTab)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGTextView, TGFrame)
__DEFINE_RQ_SIGNAL__(DataChanged, "DataChanged()")
__DEFINE_RQ_SIGNAL__1(DataDropped, "DataDropped(char *)", char*)
__DEFINE_RQ_SIGNAL__1(Marked, "Marked(Bool_t)", Bool_t)
__DEFINE_RQ_SIGNAL__1(Clicked, "Clicked(char *)", char*)
__DEFINE_RQ_SIGNAL__1(DoubleClicked, "DoubleClicked(char *)", char*)
END__DEFINE_RQ_SIGNAL_CLASS(TGTextView)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGTextEdit, TGTextView)
__DEFINE_RQ_SIGNAL__(FindAgain, "FindAgain()")
__DEFINE_RQ_SIGNAL__(Closed, "Closed()")
__DEFINE_RQ_SIGNAL__(Opened, "Opened()")
__DEFINE_RQ_SIGNAL__(Saved, "Saved()")
__DEFINE_RQ_SIGNAL__(SavedAs, "SavedAs()")
END__DEFINE_RQ_SIGNAL_CLASS(TGTextEdit)

START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSearchDialog, TGFrame)
__DEFINE_RQ_SIGNAL__1(TextEntered, "TextEntered(const char *)", const char*)
END__DEFINE_RQ_SIGNAL_CLASS(TGSearchDialog)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGTextEntry, TGFrame)
__DEFINE_RQ_SIGNAL__1(TextChanged, "TextChanged(char*)", char*)
__DEFINE_RQ_SIGNAL__(ReturnPressed, "ReturnPressed()")
__DEFINE_RQ_SIGNAL__(TabPressed, "TabPressed()")
__DEFINE_RQ_SIGNAL__(ShiftTabPressed, "ShiftTabPressed()")
__DEFINE_RQ_SIGNAL__(CursorOutLeft, "CursorOutLeft()")
__DEFINE_RQ_SIGNAL__(CursorOutRight, "CursorOutRight()")
__DEFINE_RQ_SIGNAL__(CursorOutUp, "CursorOutUp()")
__DEFINE_RQ_SIGNAL__(CursorOutDown, "CursorOutDown()")
__DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked()")
END__DEFINE_RQ_SIGNAL_CLASS(TGTextEntry)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGToolBar, TGFrame)
__DEFINE_RQ_SIGNAL__1(Pressed, "Pressed(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(Released, "Released(Int_t)", Int_t)
__DEFINE_RQ_SIGNAL__1(Clicked, "Clicked(Int_t)", Int_t)
END__DEFINE_RQ_SIGNAL_CLASS(TGToolBar)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGToolTip, TGFrame)
__DEFINE_RQ_SIGNAL__1(Show, "Show(Int_t,Int_t)", Int_t, Int_t)
__DEFINE_RQ_SIGNAL__(Hide, "Hide()")
__DEFINE_RQ_SIGNAL__(Reset, "Reset()")
END__DEFINE_RQ_SIGNAL_CLASS(TGToolTip)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGuiBldEditor, TGFrame)
__DEFINE_RQ_SIGNAL__1(UpdateSelected, "UpdateSelected(TGFrame*)", TGFrame*)
__DEFINE_RQ_SIGNAL__1(ChangeSelected, "ChangeSelected(TGFrame*)", TGFrame*)
END__DEFINE_RQ_SIGNAL_CLASS(TGuiBldEditor)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TMessageHandler, TQObject)
__DEFINE_RQ_SIGNAL__(Added, "Added()")
__DEFINE_RQ_SIGNAL__(Removed, "Removed()")
__DEFINE_RQ_SIGNAL__(Notified, "Notified()")
END__DEFINE_RQ_SIGNAL_CLASS(TMessageHandler)

class TSocket;
START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TMonitor, TQObject)
__DEFINE_RQ_SIGNAL__1(Ready, "Ready(TSocket*)", TSocket*)
END__DEFINE_RQ_SIGNAL_CLASS(TMonitor)





START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TProof, TQObject)
__DEFINE_RQ_SIGNAL__(DisableGoAsyn, "DisableGoAsyn()")
__DEFINE_RQ_SIGNAL__(Feedback, "Feedback(TList *objs)")
__DEFINE_RQ_SIGNAL__(CloseProgressDialog, "CloseProgressDialog()")
__DEFINE_RQ_SIGNAL__1(QueryResultReady, "QueryResultReady(const char*)", const char*)
__DEFINE_RQ_SIGNAL__1(StopProcess, "StopProcess(Bool_t)", Bool_t)
__DEFINE_RQ_SIGNAL__(CloseWindow, "CloseWindow()")
__DEFINE_RQ_SIGNAL__1(LogMessage, "LogMessage(const char*,Bool_t)", const char*, Bool_t)
__DEFINE_RQ_SIGNAL__1(Progress_Long64_t__Long64_t, "Progress(Long64_t,Long64_t)", Long64_t, Long64_t)
__DEFINE_RQ_SIGNAL__1(Progress, "Progress(Long64_t,Long64_t,Long64_t,Float_t,Float_t,Float_t,Float_t)", Long64_t, Long64_t, Long64_t, Float_t, Float_t, Float_t, Float_t)
__DEFINE_RQ_SIGNAL__1(ResetProgressDialog, "ResetProgressDialog(const char*,Int_t,Long64_t,Long64_t)", const char*, Int_t, Long64_t, Long64_t)
__DEFINE_RQ_SIGNAL__1(StartupMessage, "StartupMessage(const char*,Bool_t,Int_t,Int_t)", const char*, Bool_t, Int_t, Int_t)
__DEFINE_RQ_SIGNAL__1(DataSetStatus, "DataSetStatus(const char*,Bool_t,Int_t,Int_t)", const char*, Bool_t, Int_t, Int_t)
__DEFINE_RQ_SIGNAL__1(IsDataReady, "IsDataReady(Long64_t,Long64_t)", Long64_t, Long64_t)
END__DEFINE_RQ_SIGNAL_CLASS(TProof)




class TQCommand;
START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TQCommand, TQObject)
  __DEFINE_RQ_SIGNAL__(Redo, "Redo()")
  __DEFINE_RQ_SIGNAL__(Undo, "Undo()")
  __DEFINE_RQ_SIGNAL__1(CurrentChanged,  "CurrentChanged(TQCommand*)", TQCommand*)
END__DEFINE_RQ_SIGNAL_CLASS(TQCommand)

START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TQConnection, TQObject)
  __DEFINE_RQ_SIGNAL__(Destroyed, "Destroyed()")
END__DEFINE_RQ_SIGNAL_CLASS(TQConnection)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TRootBrowser, TGFrame)
  __DEFINE_RQ_SIGNAL__1(BrowseObj, "BrowseObj(TObject*)", TObject*)
  __DEFINE_RQ_SIGNAL__1(ExecuteDefaultAction, "ExecuteDefaultAction(TObject*)", TObject*)
  __DEFINE_RQ_SIGNAL__1(DoubleClicked,  "DoubleClicked(TObject*)", TObject*)
  __DEFINE_RQ_SIGNAL__1(Checked, "Checked(TObject*,Bool_t)", TObject*, Bool_t)
END__DEFINE_RQ_SIGNAL_CLASS(TRootBrowser)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TRootBrowserLite, TGFrame)
  __DEFINE_RQ_SIGNAL__1(BrowseObj, "BrowseObj(TObject*)", TObject*)
  __DEFINE_RQ_SIGNAL__1(ExecuteDefaultAction, "ExecuteDefaultAction(TObject*)", TObject*)
  __DEFINE_RQ_SIGNAL__1(DoubleClicked, "DoubleClicked(TObject*)", TObject*)
  __DEFINE_RQ_SIGNAL__1(Checked, "Checked(TObject*,Bool_t)", TObject*, Bool_t)
END__DEFINE_RQ_SIGNAL_CLASS(TRootBrowserLite)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TNewChainDlg, TGFrame)
  __DEFINE_RQ_SIGNAL__1(OnElementSelected, "OnElementSelected(TObject *)", TObject*)
END__DEFINE_RQ_SIGNAL_CLASS(TNewChainDlg)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TSysEvtHandler, TQObject)
  __DEFINE_RQ_SIGNAL__(Activated,"Activated()")
  __DEFINE_RQ_SIGNAL__(DeActivated, "DeActivated()")
  __DEFINE_RQ_SIGNAL__(Notified, "Notified()")
  __DEFINE_RQ_SIGNAL__(Added, "Added()")
  __DEFINE_RQ_SIGNAL__(Removed, "Removed()")
END__DEFINE_RQ_SIGNAL_CLASS(TSysEvtHandler)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TTimer, TSysEvtHandler)
    __DEFINE_RQ_SIGNAL__(TurnOn, "TurnOn()")
    __DEFINE_RQ_SIGNAL__(TurnOff, "TurnOff()")
    __DEFINE_RQ_SIGNAL__(Timeout ,"Timeout()")
END__DEFINE_RQ_SIGNAL_CLASS(TTimer)





#endif // TGSignals_h__
