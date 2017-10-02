//
//  XVimWindow.h
//  XVim
//
//  Created by Tomas Lundell on 9/04/12.
//

#import <Cocoa/Cocoa.h>
#import "XVimKeyStroke.h"
#import "XVimMotion.h"

/*
 * This class manages 1 window. (The term "window" here is different from NSWindow)
 * A window has several text views and one command line view.
 * All the key input (or mouse input or some other event if needed ) must be passed to
 * the associated XVimWindow object first and it handles the event.
 */
@class CommandResponder;
@class XVimEvaluator;
@protocol SourceViewProtocol;
@protocol SourceViewXVimProtocol;


@interface XVimWindow : NSObject <NSTextInputClient, NSTextFieldDelegate>
@property (strong, readonly) id<SourceViewProtocol, SourceViewXVimProtocol> sourceView; // This represents currently focused sourceView
@property (weak, readonly) NSTextView* inputView;
@property (weak, readonly) XVimEvaluator* currentEvaluator;
@property (weak, readonly) CommandResponder* commandResponder;

- (instancetype)initWithEditorView:(id<SourceViewProtocol>)responder;
- (void)setupAfterEditorViewSetup;
- (void)handleKeyStroke:(XVimKeyStroke*)keyStroke onStack:(NSMutableArray*)stack;
- (BOOL)handleKeyEvent:(NSEvent*)event;
- (BOOL)shouldAutoCompleteAtLocation:(unsigned long long)location;

- (void)errorMessage:(NSString*)message ringBell:(BOOL)ringBell;
- (void)statusMessage:(NSString*)message;
- (void)clearErrorMessage;

- (void)setForcusBackToSourceView;

- (void)syncEvaluatorStack;

- (void)preMotion:(XVimMotion*)motion;
@end
