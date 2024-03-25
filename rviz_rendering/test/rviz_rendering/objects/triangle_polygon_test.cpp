/*
 * Copyright (c) 2024, Open Source Robotics Foundation, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
 * LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtest/gtest.h>  // NOLINT
#include <gmock/gmock.h>  // NOLINT

#include <memory>
#include <vector>

#include <Ogre.h>

#include "rviz_rendering/objects/triangle_polygon.hpp"
#include "../ogre_testing_environment.hpp"

#include "../matcher.hpp"

class TrianglePolygonTestFixture : public ::testing::Test
{
protected:
  void SetUp()
  {
    testing_environment_ = std::make_shared<rviz_rendering::OgreTestingEnvironment>();
    testing_environment_->setUpOgreTestEnvironment();
  }

  std::shared_ptr<rviz_rendering::OgreTestingEnvironment> testing_environment_;
};

TEST_F(TrianglePolygonTestFixture, setPoints_sets_the_line_position_and_size) {
  auto scene_manager = Ogre::Root::getSingletonPtr()->createSceneManager();
  auto root_node = scene_manager->getRootSceneNode();

  auto O = Ogre::Vector3(0, 0, 0);
  auto A = Ogre::Vector3(0, 1, 0);
  auto B = Ogre::Vector3(1, 0.5, 0);
  auto color = Ogre::ColourValue(255, 0, 0, 1.0);
  auto triangle_polygon = new rviz_rendering::TrianglePolygon(
    scene_manager, root_node, O, A, B, "test_triangle",
    color, false, false);

  auto manual_object = triangle_polygon->getManualObject();


  // auto triangle_node = dynamic_cast<Ogre::SceneNode *>(root_node->getChild(0));
  auto aabb = manual_object->getBoundingBox();

  ASSERT_THAT(aabb.getMinimum(), Vector3Eq(Ogre::Vector3(0, 0, 0)));
  ASSERT_THAT(aabb.getMaximum(), Vector3Eq(Ogre::Vector3(1, 1, 0)));
  delete triangle_polygon;
}
