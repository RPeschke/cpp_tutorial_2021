#ifndef TGSignals_h__
#define TGSignals_h__
#include "RQSignals.hh"





START__DEFINE_RQ_SIGNAL_BASE_CLASS(TQObject)
  __DEFINE_RQ_SIGNAL__(Destroyed,      "Destroyed()"           )
  __DEFINE_RQ_SIGNAL__(ChangedBy,      "ChangedBy(char*)"      )
  __DEFINE_RQ_SIGNAL__(Message ,       "Message(char*)"        )
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


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGButton, TPad)
  __DEFINE_RQ_SIGNAL__(Pressed, "Pressed()")
  __DEFINE_RQ_SIGNAL__(Released, "Released()")
  __DEFINE_RQ_SIGNAL__(Clicked, "Clicked()")
  __DEFINE_RQ_SIGNAL__(Toggled, "Toggled(Bool_t)")
  __DEFINE_RQ_SIGNAL__(MBPressed, "MBPressed()")
  __DEFINE_RQ_SIGNAL__(MBReleased, "MBReleased()")
  __DEFINE_RQ_SIGNAL__(MBClicked, "MBClicked()")
  __DEFINE_RQ_SIGNAL__(ItemClicked, "ItemClicked(Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGButton)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGButtonGroup, TGButton)
  __DEFINE_RQ_SIGNAL__(Pressed, "Pressed(Int_t)")
  __DEFINE_RQ_SIGNAL__(Released,"Released(Int_t)")
  __DEFINE_RQ_SIGNAL__(Clicked,"Clicked(Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGButtonGroup)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGFrame, TQObject)
  __DEFINE_RQ_SIGNAL__(ProcessedConfigure,"ProcessedConfigure(Event_t*)")
  __DEFINE_RQ_SIGNAL__(ProcessedEvent,"ProcessedEvent(Event_t*)")
  __DEFINE_RQ_SIGNAL__(CloseWindow,"CloseWindow()")
END__DEFINE_RQ_SIGNAL_CLASS(TGFrame)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGCanvas, TGFrame)
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
END__DEFINE_RQ_SIGNAL_CLASS(TGCanvas)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGClient, TQObject)
  __DEFINE_RQ_SIGNAL__(RegisteredWindow,"RegisteredWindow(Window_t)")
  __DEFINE_RQ_SIGNAL__(ProcessedEvent, "ProcessedEvent(Event_t*, Window_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGClient)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGColorDialog, TQObject)
  __DEFINE_RQ_SIGNAL__(ColorSelected, "ColorSelected(Pixel_t)")
  __DEFINE_RQ_SIGNAL__(AlphaColorSelected, "AlphaColorSelected(ULong_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGColorDialog)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGComboBox, TGFrame)
  __DEFINE_RQ_SIGNAL__(Selected_int_int, "Selected(Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected_int, "Selected(Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected_ccharStar, "Selected(char*)")
  __DEFINE_RQ_SIGNAL__(ReturnPressed,"ReturnPressed()")
END__DEFINE_RQ_SIGNAL_CLASS(TGComboBox)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGDockableFrame, TGFrame)
  __DEFINE_RQ_SIGNAL__(Docked,"Docked()")
  __DEFINE_RQ_SIGNAL__(Undocked, "Undocked()")
END__DEFINE_RQ_SIGNAL_CLASS(TGDockableFrame)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGDoubleSlider, TGFrame)
  __DEFINE_RQ_SIGNAL__(PositionChanged,"PositionChanged()")
  __DEFINE_RQ_SIGNAL__(Pressed,"Pressed()")
  __DEFINE_RQ_SIGNAL__(Released,"Released()")
END__DEFINE_RQ_SIGNAL_CLASS(TGDoubleSlider)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGedMarkerSelect, TGButton)
  __DEFINE_RQ_SIGNAL__(MarkerSelected,"MarkerSelected(Style_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGedMarkerSelect)

START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGedPatternSelect, TGButton)
  __DEFINE_RQ_SIGNAL__(PatternSelected, "PatternSelected(Style_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGedPatternSelect)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGeoPconEditor, TGFrame)
  __DEFINE_RQ_SIGNAL__(Changed, "Changed(Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGeoPconEditor)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGEventHandler, TQObject)
  __DEFINE_RQ_SIGNAL__(ProcessedEvent, "ProcessedEvent(Event_t*)")
END__DEFINE_RQ_SIGNAL_CLASS(TGEventHandler)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGFontDialog, TGFrame)
  __DEFINE_RQ_SIGNAL__(ProcessedEvent, "ProcessedEvent(Event_t*)")
  __DEFINE_RQ_SIGNAL__(FontSelected, "FontSelected(char*)")
  __DEFINE_RQ_SIGNAL__(AlignSelected,"AlignSelected(Int_t)")
  __DEFINE_RQ_SIGNAL__(ColorSelected , "ColorSelected(Pixel_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGFontDialog)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGHtml, TGFrame)
  __DEFINE_RQ_SIGNAL__(MouseOver, "MouseOver(const char *)")
  __DEFINE_RQ_SIGNAL__(MouseDown, "MouseDown(const char *)") 
  __DEFINE_RQ_SIGNAL__(ButtonClicked, "ButtonClicked(char*,char*)") 
  __DEFINE_RQ_SIGNAL__(SubmitClicked, "SubmitClicked(char*)")
  __DEFINE_RQ_SIGNAL__(CheckToggled,  "CheckToggled(char*,Bool_t,char*)" )
  __DEFINE_RQ_SIGNAL__(RadioChanged,  "RadioChanged(char*,char*)")
  __DEFINE_RQ_SIGNAL__(InputSelected, "InputSelected(char*,char*)")
END__DEFINE_RQ_SIGNAL_CLASS(TGHtml)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGHtmlBrowser, TGFrame)
 __DEFINE_RQ_SIGNAL__(Clicked, "Clicked(char *)")
END__DEFINE_RQ_SIGNAL_CLASS(TGHtmlBrowser)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGImageMap, TGButton)
  __DEFINE_RQ_SIGNAL__ (RegionClicked,  "RegionClicked(Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_Int_t, "DoubleClicked(Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked()")
  __DEFINE_RQ_SIGNAL__(OnMouseOver, "OnMouseOver(Int_t)")
  __DEFINE_RQ_SIGNAL__(OnMouseOut, "OnMouseOut(Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGImageMap)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGLClipSetEditor, TGButton)
  __DEFINE_RQ_SIGNAL__(Changed,"Changed()")
END__DEFINE_RQ_SIGNAL_CLASS(TGLClipSetEditor)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGListBox, TGFrame)
  __DEFINE_RQ_SIGNAL__(SelectionChanged,"SelectionChanged()")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_int,"DoubleClicked(Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_int_int,"DoubleClicked(Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected_int,"Selected(Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected_int_int,"Selected(Int_t,Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGListBox)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGListTree, TGFrame)
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
END__DEFINE_RQ_SIGNAL_CLASS(TGListTree)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGListView, TGCanvas)
  __DEFINE_RQ_SIGNAL__(SelectionChanged,"SelectionChanged()")
  __DEFINE_RQ_SIGNAL__(Clicked_TGLVEntryStar_Int_t,"Clicked(TGLVEntry*,Int_t)")
  __DEFINE_RQ_SIGNAL__(Clicked_TGLVEntryStar_Int_t_Int_t_Int_t, "Clicked(TGLVEntry*,Int_t,Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_TGLVEntryStar_Int_t,   "DoubleClicked(TGLVEntry*,Int_t)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked_TGLVEntryStar_Int_t_Int_t_Int_t , "DoubleClicked(TGLVEntry*,Int_t,Int_t,Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGListView)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGLOverlayButton, TQObject)
  __DEFINE_RQ_SIGNAL__(Clicked, "Clicked(TGLViewerBase*)")
END__DEFINE_RQ_SIGNAL_CLASS(TGLOverlayButton)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGLViewer, TQObject)
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
END__DEFINE_RQ_SIGNAL_CLASS(TGLViewer)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGMdiFrame, TGFrame)
  __DEFINE_RQ_SIGNAL__(CloseWindow, "CloseWindow()")
END__DEFINE_RQ_SIGNAL_CLASS(TGMdiFrame)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGMdiMainFrame, TGCanvas)
  __DEFINE_RQ_SIGNAL__(FrameCreated,"FrameCreated(Int_t)")
  __DEFINE_RQ_SIGNAL__(FrameClosed, "FrameClosed(Int_t)")
  __DEFINE_RQ_SIGNAL__(FrameMaximized, "FrameMaximized(Int_t)")
  __DEFINE_RQ_SIGNAL__(FrameMinimized, "FrameMinimized(Int_t)") 
  __DEFINE_RQ_SIGNAL__(FrameRestored, "FrameRestored(Int_t)")
  __DEFINE_RQ_SIGNAL__(FramesArranged, "FramesArranged(Int_t)")
  __DEFINE_RQ_SIGNAL__(SetCurrent, "SetCurrent(TGMdiFrame*)")
END__DEFINE_RQ_SIGNAL_CLASS(TGMdiMainFrame)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGPopupMenu, TGFrame)
  __DEFINE_RQ_SIGNAL__(PoppedUp, "PoppedUp()")
  __DEFINE_RQ_SIGNAL__(PoppedDown, "PoppedDown()")
  __DEFINE_RQ_SIGNAL__(Highlighted, "Highlighted(Int_t)")
  __DEFINE_RQ_SIGNAL__(Activated, "Activated(Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGPopupMenu)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGNumberEntry, TGFrame)
  __DEFINE_RQ_SIGNAL__(InvalidInput, "InvalidInput(char*)")
  __DEFINE_RQ_SIGNAL__(ValueChanged,  "ValueChanged(Long_t)")
  __DEFINE_RQ_SIGNAL__(ValueSet,"ValueSet(Long_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGNumberEntry)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGScrollBar, TGFrame)
  __DEFINE_RQ_SIGNAL__(PositionChanged, "PositionChanged(Int_t)") 
  __DEFINE_RQ_SIGNAL__(RangeChanged ,  "RangeChanged(Int_t)" )
  __DEFINE_RQ_SIGNAL__(PageSizeChanged, "PageSizeChanged(Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGScrollBar)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGShutter, TGFrame)
  __DEFINE_RQ_SIGNAL__(Selected, " Selected()")
  __DEFINE_RQ_SIGNAL__(Selected_TGShutterItemStar, " Selected(TGShutterItem*)")
END__DEFINE_RQ_SIGNAL_CLASS(TGShutter)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSlider, TGFrame)
  __DEFINE_RQ_SIGNAL__(PositionChanged, "PositionChanged(Int_t)")
  __DEFINE_RQ_SIGNAL__(Pressed, "Pressed()")
  __DEFINE_RQ_SIGNAL__(Released ,"Released()")
END__DEFINE_RQ_SIGNAL_CLASS(TGShutter)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSpeedo, TGFrame)
  __DEFINE_RQ_SIGNAL__(OdoClicked,"OdoClicked()")
  __DEFINE_RQ_SIGNAL__(LedClicked,"LedClicked()")
END__DEFINE_RQ_SIGNAL_CLASS(TGSpeedo)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSplitFrame, TGFrame)
 __DEFINE_RQ_SIGNAL__(Docked,"Docked(TGFrame*)" )
 __DEFINE_RQ_SIGNAL__(Undocked, "Undocked(TGFrame*)" )
END__DEFINE_RQ_SIGNAL_CLASS(TGSplitFrame)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSplitter, TGFrame)
  __DEFINE_RQ_SIGNAL__(DragStarted,"DragStarted()" )
  __DEFINE_RQ_SIGNAL__(Moved, "Moved(Int_t)" )
  __DEFINE_RQ_SIGNAL__(LayoutHeader, "LayoutHeader(TGFrame*)")
  __DEFINE_RQ_SIGNAL__(LayoutListView, "LayoutListView()")
  __DEFINE_RQ_SIGNAL__(ButtonPressed, "ButtonPressed()")
  __DEFINE_RQ_SIGNAL__(ButtonReleased, "ButtonReleased()")
  __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked(TGVFileSplitter*)")
END__DEFINE_RQ_SIGNAL_CLASS(TGSplitter)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGTab, TGFrame)
  __DEFINE_RQ_SIGNAL__(CloseTab,"CloseTab(Int_t)")
  __DEFINE_RQ_SIGNAL__(Removed, "Removed(Int_t)")
  __DEFINE_RQ_SIGNAL__(Selected , "Selected(Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGTab)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGTextView, TGFrame)
  __DEFINE_RQ_SIGNAL__(DataChanged, "DataChanged()")
  __DEFINE_RQ_SIGNAL__(DataDropped, "DataDropped(char *)")
  __DEFINE_RQ_SIGNAL__(Marked, "Marked(Bool_t)")
  __DEFINE_RQ_SIGNAL__(Clicked, "Clicked(char *)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked(char *)")
END__DEFINE_RQ_SIGNAL_CLASS(TGTextView)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGTextEdit, TGTextView)
  __DEFINE_RQ_SIGNAL__(FindAgain , "FindAgain()")
  __DEFINE_RQ_SIGNAL__(Closed, "Closed()")
  __DEFINE_RQ_SIGNAL__(Opened, "Opened()")
  __DEFINE_RQ_SIGNAL__(Saved, "Saved()")
  __DEFINE_RQ_SIGNAL__(SavedAs, "SavedAs()")
END__DEFINE_RQ_SIGNAL_CLASS(TGTextEdit)

START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGSearchDialog, TGFrame)
  __DEFINE_RQ_SIGNAL__(TextEntered, "TextEntered(const char *)")
END__DEFINE_RQ_SIGNAL_CLASS(TGSearchDialog)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGTextEntry, TGFrame)
  __DEFINE_RQ_SIGNAL__(TextChanged, "TextChanged(char*)")
  __DEFINE_RQ_SIGNAL__(ReturnPressed, "ReturnPressed()")
  __DEFINE_RQ_SIGNAL__(TabPressed, "TabPressed()")
  __DEFINE_RQ_SIGNAL__(ShiftTabPressed, "ShiftTabPressed()")
  __DEFINE_RQ_SIGNAL__(CursorOutLeft, "CursorOutLeft()")
  __DEFINE_RQ_SIGNAL__(CursorOutRight, "CursorOutRight()")
  __DEFINE_RQ_SIGNAL__(CursorOutUp,  "CursorOutUp()")
  __DEFINE_RQ_SIGNAL__(CursorOutDown, "CursorOutDown()")
  __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked()")
END__DEFINE_RQ_SIGNAL_CLASS(TGTextEntry)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGToolBar, TGFrame)
 __DEFINE_RQ_SIGNAL__(Pressed, "Pressed(Int_t)")
 __DEFINE_RQ_SIGNAL__(Released, "Released(Int_t)")
 __DEFINE_RQ_SIGNAL__(Clicked , "Clicked(Int_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TGToolBar)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGToolTip, TGFrame)
  __DEFINE_RQ_SIGNAL__(Show, "Show(Int_t,Int_t)")
  __DEFINE_RQ_SIGNAL__(Hide, "Hide()")
  __DEFINE_RQ_SIGNAL__(Reset, "Reset()")
END__DEFINE_RQ_SIGNAL_CLASS(TGToolTip)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TGuiBldEditor, TGFrame)
  __DEFINE_RQ_SIGNAL__(UpdateSelected, "UpdateSelected(TGFrame*)")
  __DEFINE_RQ_SIGNAL__(ChangeSelected,  "ChangeSelected(TGFrame*)")
END__DEFINE_RQ_SIGNAL_CLASS(TGuiBldEditor)



START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TMessageHandler, TQObject)
  __DEFINE_RQ_SIGNAL__(Added, "Added()")
  __DEFINE_RQ_SIGNAL__(Removed, "Removed()")
  __DEFINE_RQ_SIGNAL__(Notified, "Notified()")
END__DEFINE_RQ_SIGNAL_CLASS(TMessageHandler)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TMonitor, TQObject)
  __DEFINE_RQ_SIGNAL__(Ready, "Ready(TSocket*)")
END__DEFINE_RQ_SIGNAL_CLASS(TMonitor)





START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TProof, TQObject)
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
END__DEFINE_RQ_SIGNAL_CLASS(TProof)




START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TQCommand, TQObject)
  __DEFINE_RQ_SIGNAL__(Redo, "Redo()")
  __DEFINE_RQ_SIGNAL__(Undo, "Undo()")
  __DEFINE_RQ_SIGNAL__(CurrentChanged,  "CurrentChanged(TQCommand*)")
END__DEFINE_RQ_SIGNAL_CLASS(TQCommand)

START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TQConnection, TQObject)
  __DEFINE_RQ_SIGNAL__(Destroyed, "Destroyed()")
END__DEFINE_RQ_SIGNAL_CLASS(TQConnection)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TRootBrowser, TGFrame)
  __DEFINE_RQ_SIGNAL__(BrowseObj, "BrowseObj(TObject*)")
  __DEFINE_RQ_SIGNAL__(ExecuteDefaultAction, "ExecuteDefaultAction(TObject*)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked,  "DoubleClicked(TObject*)")
  __DEFINE_RQ_SIGNAL__(Checked, "Checked(TObject*,Bool_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TRootBrowser)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TRootBrowserLite, TGFrame)
  __DEFINE_RQ_SIGNAL__(BrowseObj, "BrowseObj(TObject*)")
  __DEFINE_RQ_SIGNAL__(ExecuteDefaultAction, "ExecuteDefaultAction(TObject*)")
  __DEFINE_RQ_SIGNAL__(DoubleClicked, "DoubleClicked(TObject*)")
  __DEFINE_RQ_SIGNAL__(Checked, "Checked(TObject*,Bool_t)")
END__DEFINE_RQ_SIGNAL_CLASS(TRootBrowserLite)


START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(TNewChainDlg, TGFrame)
  __DEFINE_RQ_SIGNAL__(OnElementSelected, "OnElementSelected(TObject *)")
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
