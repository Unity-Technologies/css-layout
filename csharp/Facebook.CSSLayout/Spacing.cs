/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

// BEGIN_UNITY @joce 11-21-2016 CompileForC#Bindings
//namespace Facebook.CSSLayout
namespace UnityEngine.CSSLayout
// END_UNITY
{
    public class Spacing
    {
        public float? Top;
        public float? Bottom;
        public float? Left;
        public float? Right;

        public Spacing(
            float? top = null,
            float? bottom = null,
            float? left = null,
            float? right = null)
        {
            Top = top;
            Bottom = bottom;
            Left = left;
            Right = right;
        }
    }
}
