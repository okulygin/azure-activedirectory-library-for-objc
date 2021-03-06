// Copyright (c) Microsoft Corporation.
// All rights reserved.
//
// This code is licensed under the MIT License.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

@class ADAuthenticationError;
@class ADURLProtocol;
@class MSIDTelemetryUIEvent;

typedef void (^ChallengeCompletionHandler)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential *credential);

@protocol ADAuthMethodHandler

+ (BOOL)handleChallenge:(NSURLAuthenticationChallenge *)challenge
                session:(NSURLSession *)session
                   task:(NSURLSessionTask *)task
               protocol:(ADURLProtocol *)protocol
      completionHandler:(ChallengeCompletionHandler)completionHandler;

+ (void)resetHandler;

@end

//Intercepts HTTPS protocol for the application in order to allow
//NTLM with client-authentication. The class is not thread-safe.
@interface ADURLProtocol : NSURLProtocol <NSURLSessionTaskDelegate, NSURLSessionDataDelegate>
{
    NSURLSessionDataTask *_dataTask;
    id<MSIDRequestContext> _context;
}

+ (void)registerHandler:(Class<ADAuthMethodHandler>)handler
             authMethod:(NSString *)authMethod;

+ (BOOL)registerProtocol:(NSString*)endURL
          telemetryEvent:(MSIDTelemetryUIEvent*)telemetryEvent;
+ (void)unregisterProtocol;

+ (void)addContext:(id<MSIDRequestContext>)context
         toRequest:(NSMutableURLRequest *)request;

@property (readonly) id<MSIDRequestContext> context;

@end
