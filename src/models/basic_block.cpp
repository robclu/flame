//==--- src/models/basic_block.cpp ------------------------- -*- C++ -*- ---==//
//
//                          Ripple - Fastpose
//
//                      Copyright (c) 2020 Ripple
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
/// \file  basic_block.cpp
/// \brief Implementation file for a basic block for a resenet.
//
//==------------------------------------------------------------------------==//

#include <ripple/flame/models/basic_block.hpp>
#include <ripple/flame/util/conv.hpp>

namespace ripple::flame::models {

BasicBlockImpl::BasicBlockImpl(
  int64_t     input_channels,
  int64_t     output_channels,
  int64_t     stride,
  DownSampler downsampler)
: _conv_1(conv_3x3(input_channels, output_channels, stride)),
  _conv_2(conv_3x3(output_channels, output_channels)),
  _norm_1(output_channels),
  _norm_2(output_channels),
  _downsampler(downsampler) {
  register_module("conv_1", _conv_1);
  register_module("conv_2", _conv_2);
  register_module("norm_1", _norm_1);
  register_module("norm_2", _norm_2);
  register_module("relu", _relu);

  if (downsampler) {
    register_module("downsampler", _downsampler);
  }
}

auto BasicBlockImpl::forward(torch::Tensor x) -> torch::Tensor {
  auto out = _conv_1->forward(x);
  out      = _norm_1->forward(out);
  out      = _relu->forward(out);
  out      = _conv_2->forward(out);
  out      = _norm_2->forward(out);

  auto residual = _downsampler ? _downsampler->forward(x) : x;
  out += residual;
  out = _relu->forward(out);

  return out;
}

} // namespace ripple::flame::models